#ifndef VIDEOWALLLIB_OSDPORT_H
#define VIDEOWALLLIB_OSDPORT_H

#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace VideoWallLib {

class OSDPort : public CDPPort
{
public:
    void Create(const char* shortName, CDPComponent* parent) override;

    CDPProperty<std::string> Text;
    CDPProperty<std::string> FontName;
    CDPProperty<std::string> FontSize;
    CDPProperty<std::string> PosX;
    CDPProperty<std::string> PosY;
    CDPProperty<float> Timeout;
    CDPProperty<std::string> FontColor;
    CDPProperty<std::string> BGColor;
};

} // namespace VideoWallLib

#endif
