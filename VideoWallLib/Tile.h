#ifndef VIDEOWALLLIB_TILE_H
#define VIDEOWALLLIB_TILE_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPPort.h>
#include <Signal/CDPSignal.h>
#include <TilePort.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include "OSDPort.h"
#include "json.hpp"
#include <Sequencer/ServiceBlock.h>

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
    void to_json();

protected:
    CDPPort pTile;
    CDPSignal<bool> CDPSignal1;
    CDPSignal<double> Brightness;
    CDPSignal<std::string> Source;
    CDPSignal<double> Zoom;
    CDPSignal<std::string> OSDText1;
    CDPSignal<std::string> OSDText2;
    CDPSignal<std::string> OSDText3;
    CDPSignal<std::string> OSDText4;
    CDPSignal<double> ZoomSpeed;
    CDPSignal<double> TiltSpeed;
    CDPSignal<double> PanSpeed;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

    std::vector<OSDPort*> osds;
    CDPSignal<std::string> o_OSDJson;
};

} // namespace VideoWallLib

#endif
