#include "SKAARHOJTCPCom.h"
#include <OSAPI/Process/OSAPISemaphore.h>
#include <exception>
using namespace VideoWallLib;

/*!
  \class VideoWallLib::SKAARHOJTCPCom
  \inmodule VideoWallLib

  \section1 Usage

  A Custom IOServer that can send/receive data using a Transport class.
*/

SKAARHOJTCPCom::SKAARHOJTCPCom()
{
}

SKAARHOJTCPCom::~SKAARHOJTCPCom()
{
    if (m_transport)
    {
        delete m_transport;
        m_transport = nullptr;
    }
}

void SKAARHOJTCPCom::Create(const char* fullName)
{
    IOServer::Create(fullName);
    PublishToMessagageHandler.Create("PublishToMessagageHandler",this);
}

void SKAARHOJTCPCom::CreateModel()
{
    IOServer::CreateModel();
    RegisterMessage(CM_TEXTCOMMAND,"Update","",(CDPOBJECT_MESSAGEHANDLER)&SKAARHOJTCPCom::MessageUpdate);
}

void SKAARHOJTCPCom::Configure(const char* componentXML)
{
    IOServer::Configure(componentXML);
    std::string longName = this->GetNodeLongName();
    std::string ConnectorName = replaceSubcomponent(longName, "VisionControllerContainer");
    PublishToMessagageHandler.ConnectTo("VWController.VisionControllerContainer"); //TCP connector and VisionController container must be in same layer
}

void SKAARHOJTCPCom::Activate()
{
    IOServer::Activate();
    // Start the Main() thread with name of the component and normal priority:
    Start(CDPTHREAD_PRIORITY_NORMAL,ShortName());
}

void SKAARHOJTCPCom::Suspend()
{
    Stop();           // set Stop flag
    m_event.Set();    // set event so that Wait in Main() completes.
    Stop(true);       // set Stop flag, block
    Delete();         // will block until thread is no longer running (for max. 2 seconds)
    IOServer::Suspend();
}

bool SKAARHOJTCPCom::IsCommProblem()
{
    return (CDPTime::GetGlobalTime()-m_lastUpdateTime>=m_transport->GetTimeout());
}

void SKAARHOJTCPCom::FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const
{
    IOServer::FillNodeChildren(serializer);
    serializer << CDP::StudioAPI::AdoptedChild(m_transport);
}

/*!
  brief Main thread function, runs asynchronously from state-machine.
*/
void SKAARHOJTCPCom::Main()
{
    while (!Stopped())
    {
        m_event.Wait();
        m_event.Reset();
        if (Stopped())
            break;

        if (m_transport->IsError())
            m_transport->Close();
        if (!m_transport->IsOpen())
        {
            if (m_transport->Open(CDP::IO::Transport::OpenMode_Send)==false && DebugLevel(DEBUGLEVEL_NORMAL))
            {
                CDPMessage("%s: Failed opening transport. Please check connection and Transport configuration.\n",CDPComponent::Name());
                OSAPISleep(100);
            }
        }
        else if (!IsCommProblem() && !IsState("Online"))
            RunInComponentThread([&]{ requestedState="Online"; });

        try
        {
            ProtocolImplementation();
        }
        catch (std::exception &ex)
        {
            CDPMessage("%s: Caught exception '%s'\n",ex.what());
            // TODO: Determine if you want to suspend the component here
            // Suspend();
            // break;
        }
        catch (...)
        {
        }
    }
    m_transport->Close();
}

void SKAARHOJTCPCom::ProtocolImplementation()
{
    // TODO: implement the protocol. Use the transport to Read and/or Write data.
    // Set
    m_lastUpdateTime = CDPTime::GetGlobalTime();

    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_received = m_transport->Read(buffer,1024);
    if (bytes_received < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {

        } else {
            perror("recv failed");
            return;
        }
    } else if (bytes_received == 0) {
        //std::cout << "No Data" << std::endl;
        return;
    } else {
        std::string data(buffer, bytes_received);
        std::stringstream ss(data);
        std::string line;

        MessageTextCommand txtMessage;
        txtMessage.SetTextCommand("HandController");
        MessagePacketHandle msg(txtMessage);
        while (std::getline(ss, line)) {
            msg.Packet().PayloadAppend(line);
        }
        PublishToMessagageHandler.SendMessage(msg);

        // Remove possible carriage return

    }
    // each time you receive a telegram.

    // See the IOServer documentation for how to implement outputDisable, and how to use the ChannelManager.

}

bool SKAARHOJTCPCom::HandleXMLElement(XMLElementEx *pEx)
{
    if (pEx->GetName()=="Transport")
    {
        m_transport = CDP::IO::Transport::Create(pEx,this);
        if (m_transport==nullptr)
            Suspend();
        else
            m_transport->Configure(pEx,this);
        return true;
    }
    return IOServer::HandleXMLElement(pEx); // call base
}

void SKAARHOJTCPCom::ProcessOffline()
{
    IOServer::ProcessOffline();
    m_event.Set(); // this triggers the main thread
}


void SKAARHOJTCPCom::ProcessOnline()
{
    IOServer::ProcessOnline();
    m_event.Set(); // this triggers the main thread
}



int SKAARHOJTCPCom::MessageUpdate(void* message)
{
    MessageTextCommandWithParameterReceive* msg = static_cast<MessageTextCommandWithParameterReceive*>(message);
    std::string strParameter(msg->parameters);
    m_transport->Write(strParameter.c_str(),strParameter.size());
    return 1;

}

unsigned int SKAARHOJTCPCom::NumberOfNodesInXml() const
{
    return 1; // Todo: Change code if there are more nodes.
}

std::string SKAARHOJTCPCom::replaceSubcomponent(const std::string& input, const std::string& newSubcomponent) {
    // Find the last dot
    std::size_t lastDot = input.rfind('.');
    if (lastDot == std::string::npos) {
        // No dot found, just return the new subcomponent
        return newSubcomponent;
    }

    // Keep everything before the last dot, then append the new subcomponent
    return input.substr(0, lastDot + 1) + newSubcomponent;
}
