#include "LayoutPort.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::LayoutPort
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for LayoutPort here.
*/

/*!
  \internal
  \brief Creates the instance. Called after constructor.
*/
void LayoutPort::Create(const char* shortName, CDPComponent* parent)
{
    CDPPort::Create(shortName, parent);
    Source01.Create("Source01",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Source02.Create("Source02",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Source03.Create("Source03",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Source04.Create("Source04",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Source11.Create("Source11",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Source12.Create("Source12",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Source13.Create("Source13",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    Source14.Create("Source14",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}
