#ifndef VIDEOWALLLIB_TIMESTAMPGENERATOR_H
#define VIDEOWALLLIB_TIMESTAMPGENERATOR_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <string>
#include <sstream>
#include <iomanip>

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
    CDPSignal<std::string> TimestampFormatted;
    CDPSignal<std::string> Format;
    CDPSignal<bool> UTC;
    CDPSignal<std::string> TZ;
    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
};

} // namespace VideoWallLib

#endif
