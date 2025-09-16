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
    MQTTPublish.Create("MQTTPublish",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionController::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS) &VisionController::ProcessNull, "Initial Null state");
    RegisterMessage(CM_TEXTCOMMAND,"ToggleFullscreen","-1 = No fullscreen",(CDPOBJECT_MESSAGEHANDLER)&VisionController::MessageToggleFullscreen);
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionController::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
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
}



int VisionController::MessageToggleFullscreen(void* message)
{
    /* Expects message to be the name of the Tile to toggle, e.g "Tile01". Alternatively "Off"*/
    MessageTextCommandWithParameterReceive* msg = static_cast<MessageTextCommandWithParameterReceive*>(message);
    std::string strParameter(msg->parameters);

    if (DebugLevel(DEBUGLEVEL_EXTENDED))
        CDPMessage("%s: TOGGLE FULLSCREEN. Message: %s\n", CDPComponent::Name(), strParameter.c_str());

    if (strParameter == "Off"){
        currentFullscreenTile = -1;
    }
    else if(StringHelpers::StartsWith(strParameter, "Tile")){

        if (CDPComponent::FindSubcomponentConnector(strParameter.c_str()) == nullptr)
            return 1;

        // Remove "Tile"
        strParameter.erase(0, 4);
        try {
            // The tens-value represents VisionController. That is already checked with connector == nullptr.
            int tileIndex = (std::stoi(strParameter) - 1) % 10;

            if (currentFullscreenTile == tileIndex)
                currentFullscreenTile = -1;
            else
                currentFullscreenTile = tileIndex;
        } catch (...) {
            CDPMessage("ERROR: %s: Invalid parameter in MessageToggleFullscreen. Received: '%s'. Expected: 'TileXX'\n", CDPComponent::Name(), strParameter.c_str());
        }
    }
    else{
        CDPMessage("ERROR: %s: Invalid parameter in MessageToggleFullscreen. Received: '%s'. Expected: 'TileXX'\n", CDPComponent::Name(), strParameter.c_str());
    }

    PublishMQTT();
    return 1;
}

void VisionController::PublishMQTT()
{
    std::string baseTopic = this->Name();
    std::replace(baseTopic.begin(), baseTopic.end(), '.', '/');

    MessageTextCommand txtMessage;
    txtMessage.SetTextCommand("Publish");
    MessagePacketHandle msg(txtMessage);

    std::vector<CDPUtils::Parameter> param = {{"Topic", baseTopic + "/Fullscreen"},{"Payload", std::to_string(currentFullscreenTile)}, {"QoS", "0"}, {"Retain", "1"}};
    std::string joined = CDPUtils::JoinParameters(param);

    msg.Packet().PayloadAppend(joined);

    MQTTPublish.SendMessage(msg);
}
