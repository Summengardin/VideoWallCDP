#ifndef VIDEOWALLLIB_LAYOUTPORT_H
#define VIDEOWALLLIB_LAYOUTPORT_H

#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace VideoWallLib {

class LayoutPort : public CDPPort
{
public:
    void Create(const char* shortName, CDPComponent* parent) override;

    CDPProperty<std::string> Source01;
    CDPProperty<std::string> Source02;
    CDPProperty<std::string> Source03;
    CDPProperty<std::string> Source04;
    CDPProperty<std::string> Source11;
    CDPProperty<std::string> Source12;
    CDPProperty<std::string> Source13;
    CDPProperty<std::string> Source14;
};

} // namespace VideoWallLib

#endif
