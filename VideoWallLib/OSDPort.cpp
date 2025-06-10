#include "OSDPort.h"

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
void OSDPort::Create(const char* shortName, CDPComponent* parent)
{
    CDPPort::Create(shortName, parent);
    TextProp.Create("TextProp",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    TextIndex.Create("TextIndex",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}
