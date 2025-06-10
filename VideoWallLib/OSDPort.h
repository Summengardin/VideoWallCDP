#ifndef VIDEOWALLLIB_OSDPORT_H
#define VIDEOWALLLIB_OSDPORT_H

#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace VideoWallLib {

class OSDPort : public CDPPort
{
public:
    void Create(const char* shortName, CDPComponent* parent) override;

    CDPProperty<std::string> TextProp;
    CDPProperty<int> TextIndex;
};

} // namespace VideoWallLib

#endif
