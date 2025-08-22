#ifndef VIDEOWALLLIB_TIMESTAMPGENERATOR_H
#define VIDEOWALLLIB_TIMESTAMPGENERATOR_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <string>
#include <sstream>
#include <iomanip>

#include "OperationUtilities/Parameters/StringParameter.h"
#include "OperationUtilities/Parameters/ToggleParameter.h"
#include "iana_posix_map.h"





namespace VideoWallLib {

class TimestampGenerator : public CDPComponent
{
public:
    TimestampGenerator();
    ~TimestampGenerator() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    StringParameter Format;
    StringParameter TZ;
    ToggleParameter UTC;
    CDPSignal<std::string> TimestampFormatted;
    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
};

} // namespace VideoWallLib

#endif
