#include "Camera.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::Camera
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for Camera here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
Camera::Camera()
{
    requestedState = "Null";
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
Camera::~Camera()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void Camera::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    MQTTPublish.Create("MQTTPublish",this);
    Width.Create("Width",this);
    Height.Create("Height",this);
    DisplayName.Create("DisplayName",this);
    IP.Create("IP",this);
    Format.Create("Format",this);
    Framerate.Create("Framerate",this);
    Type.Create("Type",this);
    URI.Create("URI",this);

    UriParser = VideoWallLib::Uri();
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void Camera::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&Camera::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void Camera::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);

    size_t len = topics.size();
    indexedSignals.resize(len);
    indexedSignalsPrev.resize(len);
    indexedSignalsChanged.resize(len);
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
void Camera::ProcessNull()
{
    ParseURI();
    IndexInputs();
    PublishMQTT();

    firstRun = false;
}

void Camera::ParseURI()  {
    try {
        if (URI != ""){
            Uri uri = UriParser.fromString(URI);

            IP = uri.host;
            if(DebugLevelForComponent(this->GetParent(),DebugLevel(DEBUGLEVEL_EXTENDED)))
                std::cout << this->Name() << ": " << uri.toStringExtended() << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        IP = "";
        URI = "";

        if(DebugLevelForComponent(this->GetParent(),DebugLevel(DEBUGLEVEL_EXTENDED)))
            std::cerr << "Invalid URI provided: " << URI.GetString() << std::endl;

    }
}


void Camera::PublishMQTT() {

    bool changeInSignals = std::any_of(indexedSignalsChanged.begin(), indexedSignalsChanged.end(), [](bool b) { return b;});
    if (!changeInSignals && !firstRun){
        if(DebugLevelForComponent(this->GetParent(),DebugLevel(DEBUGLEVEL_EXTENDED)))
            std::cout << this->Name() << ":  --->  Nothing Changed  <---  " << std::endl;
        return;
    }

    std::string baseTopic = this->Name();
    std::replace(baseTopic.begin(), baseTopic.end(), '.', '/');


    /* // Generate and publish JSON topic - Not in use anymore
    MessageTextCommand txtMessage;
    txtMessage.SetTextCommand("Publish");
    MessagePacketHandle msg(txtMessage);

    std::vector<CDPUtils::Parameter> param = {{"Topic", baseTopic},{"Payload", this->toJson().dump()}, {"QoS", "0"}, {"Retain", "1"}};
    std::string joined = CDPUtils::JoinParameters(param);

    msg.Packet().PayloadAppend(joined);

    MQTTPublish.SendMessage(msg);
    */

    for (size_t i = 0; i < topics.size(); i++){
        if (indexedSignalsChanged[i] or firstRun){
            MessageTextCommand txtMessage;
            txtMessage.SetTextCommand("Publish");
            MessagePacketHandle msg(txtMessage);

            if (DebugLevel(DEBUGLEVEL_EXTENDED)){
                std::cout << baseTopic + "/" + topics[i] << ": " << indexedSignals[i] << "\n";
            }

            std::vector<CDPUtils::Parameter> param = {{"Topic", baseTopic + "/" + topics[i]},{"Payload", indexedSignals[i]}, {"QoS", "0"}, {"Retain", "1"}};
            std::string joined = CDPUtils::JoinParameters(param);

            msg.Packet().PayloadAppend(joined);

            MQTTPublish.SendMessage(msg);
        }

    }
}


json Camera::toJson() const
{
    json out_json;

    for (size_t i = 0; i < indexedSignalsChanged.size(); ++i){
        std::string name = topics[i];
        std::string val = indexedSignals[i];

        out_json.emplace(name, val);

        if (DebugLevel(DEBUGLEVEL_EXTENDED))
            std::cout << topics[i] << ": " << indexedSignals[i] << "\n";
    }

    return out_json;
}

void Camera::IndexInputs()
{
    // Get new values
    indexedSignals.at(0) = DisplayName;
    indexedSignals.at(1) = IP;
    indexedSignals.at(2) = URI;
    indexedSignals.at(3) = std::to_string(Width);
    indexedSignals.at(4) = std::to_string(Height);
    indexedSignals.at(5) = std::to_string(Framerate);
    indexedSignals.at(6) = Format;
    indexedSignals.at(7) = Type;

    // Check for changes
    std::transform(indexedSignals.begin(), indexedSignals.end(), indexedSignalsPrev.begin(), indexedSignalsChanged.begin(), std::not_equal_to<std::string>());

    // Store new values
    std::copy(indexedSignals.begin(), indexedSignals.end(), indexedSignalsPrev.begin());
}



