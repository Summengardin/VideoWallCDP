#include "CameraMotionReferencePort.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::CameraMotionReferencePort
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for CameraMotionReferencePort here.
*/

/*!
  \internal
  \brief Creates the instance. Called after constructor.
*/
void CameraMotionReferencePort::Create(const char* shortName, CDPComponent* parent)
{
    CDPPort::Create(shortName, parent);
    tilt_ref.Create("tilt_ref",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
    pan_ref.Create("pan_ref",this,CDPPropertyBase::e_Attribute,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}
