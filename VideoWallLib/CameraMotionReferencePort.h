#ifndef VIDEOWALLLIB_CAMERAMOTIONREFERENCEPORT_H
#define VIDEOWALLLIB_CAMERAMOTIONREFERENCEPORT_H

#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace VideoWallLib {

class CameraMotionReferencePort : public CDPPort
{
public:
    void Create(const char* shortName, CDPComponent* parent) override;

    CDPProperty<double> tilt_ref;
    CDPProperty<double> pan_ref;
};

} // namespace VideoWallLib

#endif
