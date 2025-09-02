#include "VisionController.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::VisionController
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for VisionController here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
VisionController::VisionController()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
VisionController::~VisionController()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionController::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    numTiles.Create("numTiles",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionController::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&VisionController::ProcessNull, "Initial Null state");
    RegisterMessage(CM_TEXTCOMMAND,"TileMessageHandler","",(CDPOBJECT_MESSAGEHANDLER)&VisionController::MessageTileMessageHandler);
    RegisterMessage(CM_TEXTCOMMAND,"Publish","",(CDPOBJECT_MESSAGEHANDLER)&VisionController::MessagePublish);
    RegisterMessage(CM_TEXTCOMMAND,"HandController","",(CDPOBJECT_MESSAGEHANDLER)&VisionController::MessageHandController);
    RegisterMessage(CM_TEXTCOMMAND,"MessageHandler","",(CDPOBJECT_MESSAGEHANDLER)&VisionController::MessageMessageHandler);
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionController::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
    for (auto child : GetChildren())
    {
        if (child->GetNodeType() == CDP::StudioAPI::eCDP_COMPONENT_NODE)
        {
            if (auto subcomponent = const_cast<CDPComponent*>(dynamic_cast<const CDPComponent*>(child)))
            {
                // Note: Consider using a CDPConnector instead of directly accessing a subcomponent pointer
                // OSAPIMutexLocker lock(subcomponent->GetMemberAccessMutex());
                tiles.push_back(child->GetNodeLongName());
                // std::string name = "Connector_"+ std::to_string(i);
                // CDPConnector connector;
                // connector.Create("Connector", this);
                // connector.ConnectTo(subcomponent->GetNodeLongName().c_str());
                // TileConnectors.emplace_back(connector);

                TileConnectors.push_back(std::make_unique<CDPConnector>());
                TileConnectors.back()->Create("Connector", this);
                TileConnectors.back()->ConnectTo(subcomponent->GetNodeLongName().c_str());
                // std::cout << subcomponent->GetNodeLongName().c_str()<<"\n";


                // lock.Release();
                // ProcessChild(subcomponent);
            }
        }
    }
    numTiles = tiles.size();
    // std::cout << TileConnectors.size() << "\n";
}

/*!
 \brief Component Null state processing function

 Write your component's processing code here. When the component is simple, all the processing code may reside here.
 This function gets called periodically. The period is changed by setting the "fs" (frequency) Property when you use
 the component in a project.
 Functions called ProcessSTATENAME(), like ProcessNull(), are state processing functions and are only called when
 components are in given state. The default component state is "Null".
 Note, that state processing functions are not allowed to block (i.e. read files, sleep, communicate with network in
 blocking mode etc.) For blocking code use the 'Threaded Component Model' wizard instead.

 Please consult CDP Studio "Code Mode Manual" for more information and examples.
*/
void VisionController::ProcessNull()
{
    /* Write your code here */
    // MessageTextCommand txtMessage;
    // txtMessage.SetTextCommand("test");
    // MessagePacketHandle msg(txtMessage);
    // msg.Packet().PayloadAppend(TileConnectors[0]->GetNodeName());
    // TileConnectors[0]->SendMessage(msg);

}



int VisionController::MessageTileMessageHandler(void* message)
{
    return 1;

}



int VisionController::MessagePublish(void* message)
{
    // std::cout << message << "\n";
    return 1;

}



int VisionController::MessageHandController(void* message)
{
    // std::cout << "recieved Message \n";
    return 1;

}



int VisionController::MessageMessageHandler(void* message)
{
    MessageTextCommandWithParameterReceive* msg = static_cast<MessageTextCommandWithParameterReceive*>(message);
    std::string strParameter(msg->parameters);
    std::cout << this->GetNodeLongName() << " " << strParameter << "\n";
    return 1;

}
