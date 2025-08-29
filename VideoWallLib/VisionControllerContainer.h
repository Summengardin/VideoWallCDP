#ifndef VIDEOWALLLIB_VISIONCONTROLLERCONTAINER_H
#define VIDEOWALLLIB_VISIONCONTROLLERCONTAINER_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <CDPSystem/Base/CDPPort.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include "handControllerEasy.h"
#include <Generic/CDPUtils.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>

namespace VideoWallLib {

class VisionControllerContainer : public CDPComponent
{
public:
    VisionControllerContainer();
    ~VisionControllerContainer() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;
    int MessageHandController(void* message);
    int MessageCurrentTileSource(void* message);
    int MessageReceived(void* message);
    std::vector<std::string> visionControllers;
    int numTiles;
    int numCameras;


protected:
    CDPConnector HandControllerConnector;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
    HandController HC;
    void updateHCStates(const std::string& msg);
    std::string replaceSubcomponent(const std::string& input, const std::string& newSubcomponent);
    std::vector<std::unique_ptr<CDPConnector>> TileConnectors;
    std::vector<std::string> tileSources;
    void SendTileConfiguration(bool allowedChangeTileSource);
    void UpdateHCVisual();
    MessageTextCommand txtMessage;
    MessagePacketHandle Outputmsg;
    CDPConnector MQTTSubscribe;
    float normalizeSpeed(int value);
    bool firstRun;
    std::map<int, std::string> idToCamera;
    std::map<std::string, int> cameraToId;
    bool allowedChangeTileSource;
    std::string CameraName;
    bool MessageRecieved;
    int MessageSubscribed(void* message);
    std::string extractPayload(const std::string& input);
    bool isInteger(const std::string& s);
};

} // namespace VideoWallLib

#endif
