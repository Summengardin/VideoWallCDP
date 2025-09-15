#ifndef VIDEOWALLLIB_TILE_H
#define VIDEOWALLLIB_TILE_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <CDPSystem/Base/CDPPort.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <Signal/CDPSignal.h>
#include <Generic/CDPUtils.h>
#include <chrono>

#include "OperationUtilities/OperationUtilities/Signals/DeliveryConfigString.h"
#include "OperationUtilities/Strings/StringHelpers.h"
#include "OSDTextPort.h"
#include "OSDRectPort.h"
#include "json.hpp"

using nlohmann::json;
using OperationUtilities::DeliveryConfigString;


namespace VideoWallLib {

class Tile : public CDPComponent
{
public:
    Tile();
    ~Tile() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;
    int MessageUpdateSignalsFromHC(void* message);

protected:
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
    using clock = std::chrono::steady_clock;

    DeliveryConfigString Source;
    CDPSignal<double> ZoomSpeed;
    CDPSignal<double> ZoomAbs;
    CDPSignal<double> PanSpeed;
    CDPSignal<double> PanAbs;
    CDPSignal<double> TiltSpeed;
    CDPSignal<double> TiltAbs;
    CDPSignal<double> Brightness;

    std::chrono::seconds kHoldFor{3};
    std::vector<clock::time_point> holdUntil;
    
    std::vector<std::string> topics {"Source","Brightness","ZoomAbs","ZoomSpeed","PanAbs","PanSpeed","TiltAbs","TiltSpeed","OSD"};
    std::vector<std::string> indexedSignals;
    std::vector<std::string> indexedSignalsPrev;
    std::vector<bool> indexedSignalsChanged;
    
    CDPConnector MQTTPublish;
    CDPConnector connCurrentSource;
    
    OSDRectPort SelectedRect;
    std::vector<OSDTextPort*> m_osdPorts;
    std::vector<OSDRectPort*> m_osdRectPorts;

    bool firstRun {true};

    void PublishMqtt();
    void IndexInputs();
    json OSDPortsToJson();
    void ParseAndSetSignals(const std::string& msg);
    void ConnectToSource();
    void Update();
};

} // namespace VideoWallLib

#endif
