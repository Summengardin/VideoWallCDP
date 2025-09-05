#ifndef VIDEOWALLLIB_CAMERACONTAINER_H
#define VIDEOWALLLIB_CAMERACONTAINER_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>

namespace VideoWallLib {

class CameraContainer : public CDPComponent
{
public:
    CameraContainer();
    ~CameraContainer() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    CDPSignal<int> numCameras;
    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
};

} // namespace VideoWallLib

#endif
