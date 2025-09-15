#ifndef VIDEOWALLLIB_CAMERAMOTIONREFERENCECALCULATION_H
#define VIDEOWALLLIB_CAMERAMOTIONREFERENCECALCULATION_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <Kinematics/Position.h>
#include <Signal/CDPSignal.h>
#include <VideoWallLib/CameraMotionReferencePort.h>

namespace VideoWallLib {

class CameraMotionReferenceCalculation : public CDPComponent
{
public:
    CameraMotionReferenceCalculation();
    ~CameraMotionReferenceCalculation() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    VideoWallLib::CameraMotionReferencePort Out;
    Kinematics::Position Position;
    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
};

} // namespace VideoWallLib

#endif
