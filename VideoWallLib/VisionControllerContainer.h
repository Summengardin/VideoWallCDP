#ifndef VIDEOWALLLIB_VISIONCONTROLLERCONTAINER_H
#define VIDEOWALLLIB_VISIONCONTROLLERCONTAINER_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <CDPSystem/Base/CDPPort.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include "handControllerEasy.h"
#include <CameraMotionReferencePort.h>
#include <Generic/CDPUtils.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include "OperationUtilities/Parameters/calibrationparameter.h"
#include <chrono>

class Timer {
public:
    using clock = std::chrono::steady_clock;
    using time_point = std::chrono::time_point<clock>;

    Timer() : start(clock::now()) {}

    // reset timer
    void reset() {
        start = clock::now();
    }

    // elapsed time in seconds
    long long elapsedSeconds() const {
        return std::chrono::duration_cast<std::chrono::seconds>(clock::now() - start).count();
    }

    // elapsed time in milliseconds
    long long elapsedMillis() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - start).count();
    }

private:
    time_point start;
};


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
    CameraMotionReferencePort AngleTrackingReferences;
    OperationUtilities::CalibrationParameter PanZero;
    OperationUtilities::CalibrationParameter TiltZero;
    CDPSignal<int> selectedTile;
    CDPSignal<int> ModeSelector;
    CDPConnector HandControllerConnector;
    void updateHCStates(const std::string& msg);
    void UpdateHCVisual();

    std::vector<std::unique_ptr<CDPConnector>> TileConnectors;
    std::vector<std::string> tileSources;
    void SendTileConfiguration(bool changeSource);
    bool allowedChangeTileSource;
    bool firstRunConfig;
    Timer ConfigTimer;

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

    std::array <double, 2> trackingOffset; // Offset in Pan and Tilt
    bool oldTrackingStatus;
    std::array <double, 2> oldReferance;
};

} // namespace VideoWallLib

#endif
