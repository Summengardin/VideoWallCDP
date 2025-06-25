#include "SKAARHOJRawPanelIO.h"
#include <OSAPI/Process/OSAPISemaphore.h>
#include <exception>
using namespace VideoWallLib;

/*!
  \class VideoWallLib::SKAARHOJRawPanel
  \inmodule VideoWallLib

  \section1 Usage

  A Custom IOServer that can send/receive data using a Transport class.
*/

SKAARHOJRawPanelIO::SKAARHOJRawPanelIO() {
}

SKAARHOJRawPanelIO::~SKAARHOJRawPanelIO() {
  if (m_transport) {
    delete m_transport;
    m_transport = nullptr;
  }
}

void SKAARHOJRawPanelIO::Create(const char *fullName) {
  IOServer::Create(fullName);
  PanelBrightnessPercent.Create("PanelBrightnessPercent",this);
  HCOUT.Create("HCOUT",this);
}

void SKAARHOJRawPanelIO::CreateModel() {
  IOServer::CreateModel();
}

void SKAARHOJRawPanelIO::Configure(const char *componentXML) {
  IOServer::Configure(componentXML);

  HandController.SetSenderCallback(
    [&](const std::string& command ) {
      m_transport->Write(command.c_str(), command.size());
    });


  auto PrintCB = [&](int id, const std::string& eventType, const std::string& data) {
    // std::cout << "HWCID: " << id << " TYPE: " << eventType << " DATA: " << data << std::endl;
    MessageTextCommand txtMessage;
    txtMessage.SetTextCommand("Publish");
    MessagePacketHandle msg(txtMessage);

    std::string payload = "ID: " + std::to_string(id) + " EVENT: " + eventType + " DATA: " + data;
    msg.Packet().PayloadAppend(payload);
    HCOUT.SendMessage(msg);

    if (eventType == "Down")
      HandController.setHwcState(id, SKHOJ::HWCState::ON);
    else
      HandController.setHwcState(id, SKHOJ::HWCState::DIMMED);
    if (id == 10 && eventType == "Rotate")
      PanelBrightnessPercent += std::stoi(data) * 8;

    HandController.SetPanelBrightnessPercent(PanelBrightnessPercent);

    HandController.setDisplayTextAll(PanelBrightnessPercent);
  };


  auto panelbrightnessCB = [&](int id, const std::string& eventType, const std::string& data) {
    // std::cout << "HWCID: " << id << " TYPE: " << eventType << " DATA: " << data << std::endl;
    MessageTextCommand txtMessage;
    txtMessage.SetTextCommand("Publish");
    MessagePacketHandle msg(txtMessage);

    std::string payload = "ID: " + std::to_string(id) + " EVENT: " + eventType + " DATA: " + data;
    msg.Packet().PayloadAppend(payload);
    HCOUT.SendMessage(msg);

    if (eventType == "Down")
      HandController.setHwcState(id, SKHOJ::HWCState::ON);
    else
      HandController.setHwcState(id, SKHOJ::HWCState::DIMMED);
    HandController.SetPanelBrightnessPercent(100);

    HandController.setDisplayTextAll(987);
  };

  HandController.RegisterComponent(std::make_shared<SKHOJ::DPad>(1, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::DPad>(2, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::DPad>(3, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::DPad>(4, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::DPad>(5, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::DPad>(6, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::JoyStick>(7, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::JoyStick>(8, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::JoyStick>(9, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::Encoder>(10, PrintCB));
  HandController.RegisterComponent(std::make_shared<SKHOJ::Encoder>(11, PrintCB));


}

void SKAARHOJRawPanelIO::Activate() {
  IOServer::Activate();
  // Start the Main() thread with name of the component and normal priority:
  Start(CDPTHREAD_PRIORITY_NORMAL, ShortName());
}

void SKAARHOJRawPanelIO::Suspend() {
  Stop();       // set Stop flag
  m_event.Set();// set event so that Wait in Main() completes.
  Stop(true);   // set Stop flag, block
  Delete();     // will block until thread is no longer running (for max. 2 seconds)
  IOServer::Suspend();
}

bool SKAARHOJRawPanelIO::IsCommProblem() {
  return (CDPTime::GetGlobalTime() - m_lastUpdateTime >= m_transport->GetTimeout());
}

void SKAARHOJRawPanelIO::FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const {
  IOServer::FillNodeChildren(serializer);
  serializer << CDP::StudioAPI::AdoptedChild(m_transport);
}

/*!
  brief Main thread function, runs asynchronously from state-machine.
*/
void SKAARHOJRawPanelIO::Main() {
  while (!Stopped()) {
    m_event.Wait();
    m_event.Reset();
    if (Stopped())
      break;

    if (m_transport->IsError())
      m_transport->Close();
    if (!m_transport->IsOpen()) {
      if (m_transport->Open(CDP::IO::Transport::OpenMode_Listen) == false && DebugLevel(DEBUGLEVEL_NORMAL)) {
        CDPMessage("%s: Failed opening transport. Please check connection and Transport configuration.\n", CDPComponent::Name());
        OSAPISleep(100);
      }
    }
    else if (!IsCommProblem() && !IsState("Online"))
      RunInComponentThread([&] {
        requestedState = "Online";
      });

    try {
      ProtocolImplementation();
    } catch (std::exception &ex) {
      CDPMessage("%s: Caught exception '%s'\n", ex.what());
      // TODO: Determine if you want to suspend the component here
      // Suspend();
      // break;
    } catch (...) {
    }
  }
  m_transport->Close();
}

void SKAARHOJRawPanelIO::ProtocolImplementation() {
  // TODO: implement the protocol. Use the transport to Read and/or Write data.
  // Set

  const int bufferSize = 1024;
  char buffer[bufferSize];

  CDPTimer roundtriptime_measurement;
  roundtriptime_measurement.Start();

  unsigned int bytesRead = m_transport->Read(buffer, bufferSize);
  m_lastUpdateTime = CDPTime::GetGlobalTime();

  if (bytesRead <= 0){
    if (DebugLevel(DEBUGLEVEL_EXTENDED)) CDPMessage("Read empty buffer");
  }
  else {
    std::string packet(buffer, bytesRead);
    std::istringstream stream(packet);
    std::string line;

    while (std::getline(stream, line)){
      std::string outputLine = "";

      if (line == "list")
        outputLine = "ActivePanel=1\n";
      else if (line == "ping")
        outputLine = "ack\n";
      else
        HandController.HandleCommand(line);
      // else if (line == "HWC#10=Press"){
      //   MessageTextCommand txtMessage;
      //   txtMessage.SetTextCommand("Publish");
      //   MessagePacketHandle msg(txtMessage);
      //   std::string content = "Pressed";
      //   msg.Packet().PayloadAppend(content);
      // }
      // else if (line == "HWC#10=Enc:1"){
      //   MessageTextCommand txtMessage;
      //   txtMessage.SetTextCommand("Publish");
      //   MessagePacketHandle msg(txtMessage);
      //   std::string content = "Increment";
      //   msg.Packet().PayloadAppend(content);
      // }
      // else if (line == "HWC#10=Enc:-1"){
      //   MessageTextCommand txtMessage;
      //   txtMessage.SetTextCommand("Publish");
      //   MessagePacketHandle msg(txtMessage);
      //   std::string content = "Decrement";
      //   msg.Packet().PayloadAppend(content);
      // }

      if ( outputLine.size() > 0 && !(m_transport->Write( outputLine.c_str(), outputLine.size() ) == outputLine.size()) )
        std::cout << "Could not send \"" << outputLine << "\"";
    }

    OSAPIMutexLocker locker(GetMemberAccessMutex(),"Main thread member access"); // automatic unlock when object is destroyed
    locker.Lock();
    m_SendReceiveRoundtrip.SetDouble(roundtriptime_measurement.TimeElapsed());
    locker.Release();
    // each time you receive a telegram.
  }


  // HandController.SetEncoderPressMode(0);

  // See the IOServer documentation for how to implement outputDisable, and how to use the ChannelManager.
}

bool SKAARHOJRawPanelIO::HandleXMLElement(XMLElementEx *pEx) {
  if (pEx->GetName() == "Transport") {
    m_transport = dynamic_cast<CDP::IO::TCPTransport*>( CDP::IO::Transport::Create(pEx, this) );
    if (m_transport == nullptr)
      Suspend();
    else
      m_transport->Configure(pEx, this);
    return true;
  }
  return IOServer::HandleXMLElement(pEx);// call base
}

void SKAARHOJRawPanelIO::ProcessOffline() {
  IOServer::ProcessOffline();
  m_event.Set();// this triggers the main thread
}

void SKAARHOJRawPanelIO::ProcessOnline() {
  IOServer::ProcessOnline();
  m_event.Set();// this triggers the main thread
}



unsigned int SKAARHOJRawPanelIO::NumberOfNodesInXml() const {
  return 1;// Todo: Change code if there are more nodes.
}
