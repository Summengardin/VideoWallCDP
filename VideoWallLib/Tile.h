#ifndef VIDEOWALLLIB_TILE_H
#define VIDEOWALLLIB_TILE_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPPort.h>
#include <Signal/CDPSignal.h>
#include <TilePort.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

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
    CDPPort pTile;
    CDPSignal<bool> CDPSignal1;
    CDPSignal<double> Brightness;
    CDPSignal<std::string> Source;
    CDPSignal<double> Zoom;
    CDPSignal<std::string> OSDText1;
    CDPSignal<std::string> OSDText2;
    CDPSignal<std::string> OSDText3;
    CDPSignal<std::string> OSDText4;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace VideoWallLib

#endif
