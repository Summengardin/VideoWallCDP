#include "TilePort.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::TilePort
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for TilePort here.
*/

/*!
  \internal
  \brief Creates the instance. Called after constructor.
*/
void TilePort::Create(const char* shortName, CDPComponent* parent)
{
    CDPPort::Create(shortName, parent);
    Source.Create("Source",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}
