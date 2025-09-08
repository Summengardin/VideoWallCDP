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
#include "OperationUtilities/Parameters/calibrationparameter.h"

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
    int MessageReceived(void* message);

    std::vector<std::string> visionControllers;


protected:
    OperationUtilities::CalibrationParameter numCameras;
    OperationUtilities::CalibrationParameter numTiles;

    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

    HandController HC;
    CDPSignal<int> selectedTile;
    CDPConnector HandControllerConnector;
    void updateHCStates(const std::string& msg);
    void UpdateHCVisual();

    std::vector<std::unique_ptr<CDPConnector>> TileConnectors;
    std::vector<std::string> tileSources;
    void SendTileConfiguration(bool changeSource);
    bool allowedChangeTileSource;

    MessageTextCommand txtMessage;
    MessagePacketHandle Outputmsg;
    CDPConnector MQTTSubscribe;

    std::string replaceSubcomponent(const std::string& input, const std::string& newSubcomponent);
    std::string extractPayload(const std::string& input);
    bool isInteger(const std::string& s);
    float normalizeSpeed(int value);
    std::vector<std::string> generateTileMap(int numTiles);

    std::map<int, std::string> idToCamera;
    std::map<std::string, int> cameraToId;
    std::vector<std::string> tileMap;

};

} // namespace VideoWallLib

#endif
