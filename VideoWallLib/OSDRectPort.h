#ifndef VIDEOWALLLIB_OSDRECTPORT_H
#define VIDEOWALLLIB_OSDRECTPORT_H

#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace VideoWallLib {

class OSDRectPort : public CDPPort
{
public:
    void Create(const char* shortName, CDPComponent* parent) override;

    CDPProperty<double> PosX;
    CDPProperty<double> PosY;
    CDPProperty<double> Width;
    CDPProperty<double> Height;
    CDPProperty<int> BorderWidth;
    CDPProperty<std::string> BorderColor;
    CDPProperty<int> HasBGColor;
    CDPProperty<std::string> BGColor;
    CDPProperty<std::string> Type;
    CDPProperty<double> Timeout;
    CDPProperty<bool> Enable;
};

} // namespace VideoWallLib

#endif
