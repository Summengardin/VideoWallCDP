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
    CDPProperty<int> TextIndex;
    CDPProperty<double> FontSize;
    CDPProperty<std::string> Alignment;
    CDPProperty<int> PosX;
    CDPProperty<int> PosY;
    CDPProperty<std::string> FontName;
    CDPProperty<std::string> FontColor;
    CDPProperty<std::string> BGColor;
    CDPProperty<double> Timeout;
    CDPProperty<std::string> TextIndexName;
};

} // namespace VideoWallLib

#endif
