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
    OSDTL.Create("OSDTL",this);
    OSDTC.Create("OSDTC",this);
    OSDTR.Create("OSDTR",this);
    OSDBC.Create("OSDBC",this);
    i_TiltAbs.Create("TiltAbs",this);
    i_PanAbs.Create("PanAbs",this);
    MQTTPublish.Create("MQTTPublish",this);
    i_Brightness.Create("Brightness",this);
    i_Source.Create("Source",this);
    i_ZoomAbs.Create("ZoomAbs",this);
    i_ZoomSpeed.Create("ZoomSpeed",this);
    i_TiltSpeed.Create("TiltSpeed",this);
    i_PanSpeed.Create("PanSpeed",this);
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



void Tile::index_inputs() {

    // Get new values
    indexedSignals.at(0) = i_Source;
    indexedSignals.at(1) = std::to_string(i_Brightness);
    indexedSignals.at(2) = std::to_string(i_ZoomAbs);
    indexedSignals.at(3) = std::to_string(i_ZoomSpeed);
    indexedSignals.at(4) = std::to_string(i_PanAbs);
    indexedSignals.at(5) = std::to_string(i_PanSpeed);
    indexedSignals.at(6) = std::to_string(i_TiltAbs);
    indexedSignals.at(7) = std::to_string(i_TiltSpeed);
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
