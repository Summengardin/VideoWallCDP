#include "OSDTextPort.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::OSDPort
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for OSDPort here.
*/

/*!
  \internal
  \brief Creates the instance. Called after constructor.
*/
void OSDTextPort::Create(const char* shortName, CDPComponent* parent)
{
    CDPPort::Create(shortName, parent);
    Text.Create("Text",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    TextIndex.Create("TextIndex",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    FontSize.Create("FontSize",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Alignment.Create("Alignment",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    PosX.Create("PosX",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    PosY.Create("PosY",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    FontName.Create("FontName",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    FontColor.Create("FontColor",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    BGColor.Create("BGColor",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Timeout.Create("Timeout",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    TextIndexName.Create("TextIndexName",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Type.Create("Type",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Enable.Create("Enable",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}
