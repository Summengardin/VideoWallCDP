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
#include "OperationUtilities/OperationUtilities/Signals/DeliveryConfigString.h"

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
    int MessageMessageHandler(void* message);
    void PublishMqtt();
    void IndexInputs();

protected:
    VideoWallLib::OSDPort OSDTL;
    VideoWallLib::OSDPort OSDTC;
    VideoWallLib::OSDPort OSDTR;
    VideoWallLib::OSDPort OSDBC;
    OperationUtilities::DeliveryConfigString i_Source;
    CDPSignal<double> ZoomSpeed;
    CDPSignal<double> PanSpeed;
    CDPSignal<double> ZoomAbs;
    CDPSignal<double> TiltAbs;
    CDPSignal<double> TiltSpeed;
    CDPSignal<double> Brightness;
    CDPSignal<double> PanAbs;
    CDPConnector MQTTPublish;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

    std::vector<std::string> topics = {"Source","Brightness","ZoomAbs","ZoomSpeed","PanAbs","PanSpeed","TiltAbs","TiltSpeed","OSD"};
    std::vector<std::string> indexedSignals;
    std::vector<std::string> indexedSignalsPrev;
    std::vector<bool> indexedSignalsChanged;
    std::vector<OSDPort*> m_osdPorts;
    CDPConnector VisionControllerConnector;
    CDPConnector MessageHandlerConnector;
    bool firstRun = true;

    json OSDPortsToJson();
    void parseAndSetSignals(const std::string& msg);
};

} // namespace VideoWallLib

#endif
