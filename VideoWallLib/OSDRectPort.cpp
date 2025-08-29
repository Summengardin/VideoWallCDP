#include "OSDRectPort.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::OSDRectPort
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for OSDRectPort here.
*/

/*!
  \internal
  \brief Creates the instance. Called after constructor.
*/
void OSDRectPort::Create(const char* shortName, CDPComponent* parent)
{
    CDPPort::Create(shortName, parent);
    PosX.Create("PosX",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    PosY.Create("PosY",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Width.Create("Width",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Height.Create("Height",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    BorderWidth.Create("BorderWidth",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    BorderColor.Create("BorderColor",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    HasBGColor.Create("HasBGColor",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    BGColor.Create("BGColor",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Type.Create("Type",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Timeout.Create("Timeout",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Enable.Create("Enable",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}
