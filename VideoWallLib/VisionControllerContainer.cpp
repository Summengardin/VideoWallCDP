#include "VisionControllerContainer.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::VisionControllerContainer
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for VisionControllerContainer here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
VisionControllerContainer::VisionControllerContainer()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
VisionControllerContainer::~VisionControllerContainer()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionControllerContainer::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    selectedTile.Create("selectedTile",this);
    numCameras.Create("numCameras",this);
    numTiles.Create("numTiles",this);
    MQTTSubscribe.Create("MQTTSubscribe",this);
    HandControllerConnector.Create("HandControllerConnector",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionControllerContainer::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&VisionControllerContainer::ProcessNull, "Initial Null state");
    RegisterMessage(CM_TEXTCOMMAND,"HandController","",(CDPOBJECT_MESSAGEHANDLER)&VisionControllerContainer::MessageHandController);
    RegisterMessage(CM_TEXTCOMMAND,"Received","",(CDPOBJECT_MESSAGEHANDLER)&VisionControllerContainer::MessageReceived);
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void VisionControllerContainer::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
    for (auto child : GetChildren())
    {
        if (child->GetNodeType() == CDP::StudioAPI::eCDP_COMPONENT_NODE)
        {
            if (auto subcomponent = const_cast<CDPComponent*>(dynamic_cast<const CDPComponent*>(child)))
            {
                for (auto subsubComponents : subcomponent->GetChildren()){
                    if (subsubComponents->GetNodeType()==CDP::StudioAPI::eCDP_COMPONENT_NODE){
                        if (auto tile = const_cast<CDPComponent*>(dynamic_cast<const CDPComponent*>(subsubComponents))){
                            TileConnectors.push_back(std::make_unique<CDPConnector>());
                            TileConnectors.back()->Create("Connector", this);
                            TileConnectors.back()->ConnectTo(tile->GetNodeLongName().c_str());
                            tileSources.push_back(tile->GetNodeLongName());
                            // std::cout << tile->GetNodeLongName().c_str() << "\n";
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; i<=numCameras;i++){
        std::ostringstream oss;
        oss << "Camera" << std::setw(2) << std::setfill('0') << i;
        std::string CameraName = oss.str();
        idToCamera[i] = CameraName;
        cameraToId[CameraName] = i;

    }
    numTiles = TileConnectors.size();
    tileMap = generateTileMap(numTiles);
    std::string longName = this->GetNodeLongName();
    std::string ConnectorSocket = replaceSubcomponent(longName, "IO.SKAARHOJTCPCom");
    HandControllerConnector.ConnectTo(ConnectorSocket.c_str());

}



void VisionControllerContainer::ProcessNull()
{
    /* Write your code here */

}



int VisionControllerContainer::MessageHandController(void* message)
{
    MessageTextCommandWithParameterReceive* msg = static_cast<MessageTextCommandWithParameterReceive*>(message);
    std::string strParameter(msg->parameters);
    if (strParameter== "RDY" || strParameter =="BSY"){
        return 1;
    } else {
        updateHCStates(strParameter);
        SendTileConfiguration(allowedChangeTileSource);
        UpdateHCVisual();
    }
    return 1;
}



int VisionControllerContainer::MessageReceived(void* message)
{
    // std::cout << "MessageRecieved \n";
    MessageTextCommandWithParameterReceive* msg = static_cast<MessageTextCommandWithParameterReceive*>(message);
    std::string strParameter(msg->parameters);
    std::string PayloadString = extractPayload(strParameter);
    if (isInteger(PayloadString)){
        HC.setEncoder(11,std::stoi(PayloadString));
        allowedChangeTileSource = true;}
    else{
        HC.setEncoder(11, cameraToId[PayloadString]);
        allowedChangeTileSource = true;
    }
    // SendTileConfiguration();
    UpdateHCVisual();
    return 1;

}



void VisionControllerContainer::updateHCStates(const std::string& msg) {
    if (msg.rfind("HWC#", 0) != 0) {
        return; // not a valid message
    }

    size_t eqPos = msg.find('=');
    if (eqPos == std::string::npos) return;

    int id = std::stoi(msg.substr(4, eqPos - 4));
    std::string payload = msg.substr(eqPos + 1);

    // Handle buttons
    if (id >= 1 && id <= 6) {
        HC.toggleButton(id);
    }
    // Handle joysticks
    else if (id >= 7 && id <= 9) {
        if (payload.rfind("Speed:", 0) == 0) {
            int speed = std::stoi(payload.substr(6));
            HC.setJoystick(id, speed);
        }
    }
    // Handle encoders
    else if (id == 10) {
        if (payload.find("Press",0)==0){
            //HC.setEncoder(id,0); // Set to value if Press signal should be used
        }
        if (payload.rfind("Enc:", 0) == 0) {
            int value = std::stoi(payload.substr(4));
            value += HC.encoders[id-10];
            if(value > numTiles-1){
                value = 0;
            } else if (value < 0){
                value = numTiles-1;
            }
            HC.setEncoder(id, value);
            selectedTile = value + 1; //Range of selector 1-numCameras
            std::string subscribingName = tileSources[HC.getEncoderState(id)] +".Source";
            std::replace(subscribingName.begin(),subscribingName.end(),'.','/');
            // std::cout << subscribingName << "\n";
            txtMessage.SetTextCommand("Subscribe");
            Outputmsg = txtMessage;
            std::vector<CDPUtils::Parameter> param = {{"Topic", subscribingName}, {"QoS", "0"}};
            std::string joined = CDPUtils::JoinParameters(param);
            Outputmsg.Packet().PayloadAppend(joined);
            MQTTSubscribe.SendMessage(Outputmsg);
            allowedChangeTileSource = false;
        }
    }
    else if (id == 11) {
        if (payload.find("Press",0)==0){
            //HC.setEncoder(id,0); // Set to value if Press signal should be used
        }
        if (payload.rfind("Enc:", 0) == 0) {
            int value = std::stoi(payload.substr(4));
            value += HC.encoders[id-10];
            if(value > numCameras){
                value = 1;
            } else if (value < 1){
                value = numCameras;
            }
            HC.setEncoder(id, value);
        }
    }
}


std::string VisionControllerContainer::replaceSubcomponent(const std::string& input, const std::string& newSubcomponent) {
    // Find the last dot
    std::size_t lastDot = input.rfind('.');
    if (lastDot == std::string::npos) {
        // No dot found, just return the new subcomponent
        return newSubcomponent;
    }

    // Keep everything before the last dot, then append the new subcomponent
    return input.substr(0, lastDot + 1) + newSubcomponent;
}

void VisionControllerContainer::SendTileConfiguration(bool changeSource){
    txtMessage.SetTextCommand("MessageHandler");
    Outputmsg = txtMessage;
    std::string outputline = "Zoom_speed: " + std::to_string(normalizeSpeed(HC.getJoystickState(7)))
        + "; Tilt_speed: " + std::to_string(normalizeSpeed(HC.getJoystickState(9)))
        + "; Pan_speed: " + std::to_string(normalizeSpeed(HC.getJoystickState(8)));
    if (changeSource)
        outputline += "; source: " + idToCamera[HC.getEncoderState(11)];
    outputline += +";\n";
    Outputmsg.Packet().PayloadAppend(outputline);
    TileConnectors[HC.getEncoderState(10)]->SendMessage(Outputmsg);
}


void VisionControllerContainer::UpdateHCVisual(){

    std::string outputline = "";
    outputline += HC.updateButtons(outputline);
    outputline +=HC.updateEnc(outputline, tileMap);
    outputline +=HC.updateJoystick(outputline);
    txtMessage.SetTextCommand("Update");
    Outputmsg = txtMessage;
    Outputmsg.Packet().PayloadAppend(outputline);
    HandControllerConnector.SendMessage(Outputmsg);
}
float VisionControllerContainer::normalizeSpeed(int value) {
    return std::max(-1.0f, std::min(1.0f, static_cast<float>(value) / 500.0f));
}

std::string VisionControllerContainer::extractPayload(const std::string& input) {
    const std::string key = "Payload=";
    size_t start = input.find(key);
    if (start == std::string::npos) {
        return ""; // not found
    }

    start += key.length(); // move past "Payload="
    size_t end = input.find(';', start);
    if (end == std::string::npos) {
        end = input.length();
    }

    return input.substr(start, end - start);
}


bool VisionControllerContainer::isInteger(const std::string& s) {
    try {
        size_t pos;
        std::stoi(s, &pos);
        return pos == s.size(); // ensure whole string was parsed
    } catch (...) {
        return false;
    }
}

std::vector<std::string> VisionControllerContainer::generateTileMap(int numTiles) {
    std::vector<std::string> map;
    map.reserve(numTiles);

    for (int i = 0; i < numTiles; ++i) {
        int row = i / 4;      // every 4 tiles -> next row
        int col = i % 4;      // 0..3 -> column

        std::ostringstream oss;
        oss << row            // row = 0,1,2,... so output is 0,1,2...
            << std::setw(1) << std::setfill('0') << (col + 1);

        map.push_back(oss.str());
    }
    return map;
}
