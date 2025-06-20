#ifndef VIDEOWALLLIB_TILE_H
#define VIDEOWALLLIB_TILE_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <CDPSystem/Base/CDPPort.h>
#include <Signal/CDPSignal.h>
#include <TilePort.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include "OSDPort.h"
#include "json.hpp"
#include <Generic/CDPUtils.h>

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
    void PublishMqtt();

    void index_inputs();

protected:
    CDPSignal<double> i_Brightness;
    CDPSignal<std::string> i_Source;
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

    std::vector<std::string> topics = {"Source","Brightness","ZoomAbs","ZoomSpeed","PanAbs","PanSpeed","TiltAbs","TiltSpeed","OSD"};
    std::vector<std::string> indexedSignals;
    std::vector<std::string> indexedSignalsPrev;
    std::vector<bool> indexedSignalsChanged;
    std::vector<OSDPort*> m_osdPorts;
    bool firstRun = true;
};

} // namespace VideoWallLib

#endif
