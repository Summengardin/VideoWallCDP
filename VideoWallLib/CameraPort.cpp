#include "CameraPort.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::CameraPort
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for CameraPort here.
*/

/*!
  \internal
  \brief Creates the instance. Called after constructor.
*/
void CameraPort::Create(const char* shortName, CDPComponent* parent)
{
    CDPPort::Create(shortName, parent);
    Width.Create("Width",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Height.Create("Height",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    IP.Create("IP",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Framerate.Create("Framerate",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    DisplayName.Create("DisplayName",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Format.Create("Format",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}
