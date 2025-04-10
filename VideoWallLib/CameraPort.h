#ifndef VIDEOWALLLIB_CAMERAPORT_H
#define VIDEOWALLLIB_CAMERAPORT_H

#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace VideoWallLib {

class CameraPort : public CDPPort
{
public:
    void Create(const char* shortName, CDPComponent* parent) override;

    CDPProperty<int> Width;
    CDPProperty<int> Height;
    CDPProperty<std::string> IP;
    CDPProperty<float> Framerate;
    CDPProperty<std::string> DisplayName;
    CDPProperty<std::string> Format;
};

} // namespace VideoWallLib

#endif
