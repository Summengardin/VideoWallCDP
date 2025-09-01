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
#include "OSDTextPort.h"
#include "OSDRectPort.h"
#include "json.hpp"
#include "OperationUtilities/Strings/StringHelpers.h"

using json = nlohmann::json;

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


protected:
    CDPSignal<std::string> i_Source;
    CDPSignal<double> i_Brightness;
    CDPSignal<double> i_ZoomAbs;
    CDPSignal<double> i_ZoomSpeed;
    CDPSignal<double> i_TiltSpeed;
    CDPSignal<double> i_PanSpeed;
    CDPSignal<double> i_TiltAbs;
    CDPSignal<double> i_PanAbs;
    CDPConnector MQTTPublish;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
    using clock = std::chrono::steady_clock;

    OSDRectPort SelectedRect;

    std::chrono::seconds kHoldFor{3};
    std::vector<clock::time_point> holdUntil;

    std::vector<std::string> topics {"Source","Brightness","ZoomAbs","ZoomSpeed","PanAbs","PanSpeed","TiltAbs","TiltSpeed","OSD"};
    std::vector<std::string> indexedSignals;
    std::vector<std::string> indexedSignalsPrev;
    std::vector<bool> indexedSignalsChanged;
    std::vector<OSDTextPort*> m_osdPorts;
    std::vector<OSDRectPort*> m_osdRectPorts;

    bool firstRun {true};

    void PublishMqtt();
    void IndexInputs();
    json OSDPortsToJson();
};

} // namespace VideoWallLib

#endif
