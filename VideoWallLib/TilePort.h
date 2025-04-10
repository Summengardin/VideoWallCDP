#ifndef VIDEOWALLLIB_TILEPORT_H
#define VIDEOWALLLIB_TILEPORT_H

#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace VideoWallLib {

class TilePort : public CDPPort
{
public:
    void Create(const char* shortName, CDPComponent* parent) override;

    CDPProperty<std::string> Source;
};

} // namespace VideoWallLib

#endif
