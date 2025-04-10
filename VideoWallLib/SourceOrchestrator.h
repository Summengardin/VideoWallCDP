#ifndef VIDEOWALLLIB_SOURCEORCHESTRATOR_H
#define VIDEOWALLLIB_SOURCEORCHESTRATOR_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <vector>

#include "CameraPort.h"
#include "LayoutPort.h"


namespace VideoWallLib {

class SourceOrchestrator : public CDPComponent
{
public:
    SourceOrchestrator();
    ~SourceOrchestrator() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

    std::vector<CameraPort*> cameraPorts;
    LayoutPort pLayout;
    CDPSignal<std::string> S01;
    CDPSignal<std::string> S02;
    CDPSignal<std::string> S03;
    CDPSignal<std::string> S04;
    CDPSignal<std::string> S11;
    CDPSignal<std::string> S12;
    CDPSignal<std::string> S13;
    CDPSignal<std::string> S14;
};

} // namespace VideoWallLib

#endif
