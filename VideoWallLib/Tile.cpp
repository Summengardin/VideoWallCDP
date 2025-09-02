#include "Tile.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::Tile
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for Tile here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
Tile::Tile()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
Tile::~Tile()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void Tile::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    VisionControllerConnector.Create("VisionControllerConnector",this);
    MessageHandlerConnector.Create("MessageHandlerConnector",this);
    OSDTL.Create("OSDTL",this);
    OSDTC.Create("OSDTC",this);
    OSDTR.Create("OSDTR",this);
    OSDBC.Create("OSDBC",this);
    i_Source.Create("Source",this);
    ZoomSpeed.Create("ZoomSpeed",this);
    PanSpeed.Create("PanSpeed",this);
    ZoomAbs.Create("ZoomAbs",this);
    TiltAbs.Create("TiltAbs",this);
    PanAbs.Create("PanAbs",this);
    TiltSpeed.Create("TiltSpeed",this);
    Brightness.Create("Brightness",this);
    MQTTPublish.Create("MQTTPublish",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void Tile::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&Tile::ProcessNull, "Initial Null state");
    RegisterMessage(CM_TEXTCOMMAND,"MessageHandler","",(CDPOBJECT_MESSAGEHANDLER)&Tile::MessageMessageHandler);
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void Tile::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
    for (CDPPort* port: m_ports)
        if (OSDPort* osd_port = dynamic_cast<OSDPort*>(port))
            m_osdPorts.push_back(osd_port);

    indexedSignals.resize(10);
    indexedSignalsPrev.resize(10);
    indexedSignalsChanged.resize(10);
    MessageHandlerConnector.ConnectTo("VWController.VisionControllerContainer");
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
void Tile::ProcessNull()
{
        /* Write your code here */
    IndexInputs();
    PublishMqtt();

    firstRun = false;
}



int Tile::MessageMessageHandler(void* message)
{
    MessageTextCommandWithParameterReceive* msg = static_cast<MessageTextCommandWithParameterReceive*>(message);
    std::string strParameter(msg->parameters);
    parseAndSetSignals(strParameter);
    return 1;

}



void Tile::IndexInputs() {

    // Get new values
    indexedSignals.at(0) = i_Source;
    indexedSignals.at(1) = std::to_string(Brightness);
    indexedSignals.at(2) = std::to_string(ZoomAbs);
    indexedSignals.at(3) = std::to_string(ZoomSpeed);
    indexedSignals.at(4) = std::to_string(PanAbs);
    indexedSignals.at(5) = std::to_string(PanSpeed);
    indexedSignals.at(6) = std::to_string(TiltAbs);
    indexedSignals.at(7) = std::to_string(TiltSpeed);
    indexedSignals.at(8) = CDPUtils::EscapeQuotation(OSDPortsToJson().dump());

    // Check for changes
    std::transform(indexedSignals.begin(), indexedSignals.end(), indexedSignalsPrev.begin(), indexedSignalsChanged.begin(), std::not_equal_to<std::string>());

    // Store new values
    std::copy(indexedSignals.begin(), indexedSignals.end(), indexedSignalsPrev.begin());
}



void Tile::PublishMqtt() {

    bool changeInSignals = std::any_of(indexedSignalsChanged.begin(), indexedSignalsChanged.end(), [](bool b) { return b;});
    if (!changeInSignals && !firstRun){
        return;
    }

    std::string baseTopic = this->Name();
    std::replace(baseTopic.begin(), baseTopic.end(), '.', '/');

    for (size_t i = 0; i < topics.size(); i++){
        if (indexedSignalsChanged[i]){
            MessageTextCommand txtMessage;
            txtMessage.SetTextCommand("Publish");
            MessagePacketHandle msg(txtMessage);

            if (DebugLevel(DEBUGLEVEL_EXTENDED) and false){
                std::cout << baseTopic + "/" + topics[i] << ": " << indexedSignals[i] << "\n";
            }

            std::vector<CDPUtils::Parameter> param = {{"Topic", baseTopic + "/" + topics[i]},{"Payload", indexedSignals[i]}, {"QoS", "0"}, {"Retain", "1"}};
            std::string joined = CDPUtils::JoinParameters(param);

            msg.Packet().PayloadAppend(joined);

            MQTTPublish.SendMessage(msg);
        }

    }
}
json Tile::OSDPortsToJson() {
    json out_json;
    for (auto p : m_osdPorts){
        json loc_json;
        auto add_to_json = [&](IPortConnection& con){
            std::string name = con.GetConnectionName();
            // Remove "Map" from name
            name.erase(0, 3);
            std::string val = con.GetLocalValue()->GetValue();
            loc_json.emplace(name, val);
        };
        p->ForEachConnection(add_to_json);
        auto name = p->GetNodeName();
        out_json.emplace(name, loc_json);
    }
    return out_json;
}

void Tile::parseAndSetSignals(const std::string& msg) {
    std::istringstream ss(msg);
    std::string token;

    while (std::getline(ss, token, ';')) {

        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        // trim(token);
        if (token.empty()) continue;

        size_t pos = token.find(':');
        if (pos == std::string::npos) continue;

        std::string key = token.substr(0, pos);
        std::string valueStr = token.substr(pos + 1);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

        // Decide where to store
        if (key == "Zoom_speed") {
            ZoomSpeed = std::stod(valueStr);
        }
        else if (key == "Tilt_speed") {
            TiltSpeed = std::stod(valueStr);
        }
        else if (key == "Pan_speed") {
            PanSpeed = std::stod(valueStr);
        }
        else if (key == "source") {
            // std::cout << "New source value: " << valueStr << "\n";
            i_Source = valueStr;
        }
    }
}
