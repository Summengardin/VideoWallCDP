#ifndef VIDEOWALLLIB_OSDDATADISTRIBUTOR_H
#define VIDEOWALLLIB_OSDDATADISTRIBUTOR_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <sstream>

#include <OSDPort.h>

namespace VideoWallLib {

class OSDDataDistributor : public CDPComponent
{
public:
    OSDDataDistributor();
    ~OSDDataDistributor() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

    void index_inputs();

protected:
    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;

    std::vector<OSDPort*> m_osdports;
    std::vector<std::string> indexed_data = std::vector<std::string>(10);
    CDPSignal<double> i_GangwayLoad;
    CDPSignal<double> i_CraneLoad;
    CDPSignal<std::string> i_Mode;
    CDPSignal<bool> i_ShowOSDDescription;
};

} // namespace VideoWallLib

#endif
