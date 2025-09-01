#include "Camera.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::Camera
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for Camera here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
Camera::Camera()
{
    requestedState = "Null";
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
Camera::~Camera()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void Camera::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    URI.Create("URI",this);
    DisplayName.Create("DisplayName",this);
    IP.Create("IP",this);
    Format.Create("Format",this);
    Type.Create("Type",this);
    pCamera.Create("pCamera",this);
    Width.Create("Width",this);
    Height.Create("Height",this);
    // DisplayName.Create("DisplayName",this);
    // IP.Create("IP",this);
    // Format.Create("Format",this);
    Framerate.Create("Framerate",this);
    // Type.Create("Type",this);
    // URI.Create("URI",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void Camera::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&Camera::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void Camera::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
    uri = VideoWallLib::Uri();
}

/*!
 \brief Component Null state processing function

 Write your component's processing code here. When the component is simple, all the processing code may reside here.
 This function gets called periodically. The period is changed by setting the "fs" (frequency) Property when you use
 the component in a project.
 Functions called ProcessSTATENAME(), like ProcessNull(), are state processing functions and are only called when
 components are in given state. The default component state is "Null".
 Note, that state processing functions are not allowed to block (i.e. read files, sleep, communicate with network in
 blocking mode etc.) For blocking code use the 'Threaded Component Model' wizard instead.

 Please consult CDP Studio "Code Mode Manual" for more information and examples.
*/
void Camera::ProcessNull()
{
    uri.parse(URI.GetString());
    IP = uri.host;
    if(DebugLevel(DEBUGLEVEL_EXTENDED))
        std::cout << this->Name() << ": " << uri.toStringExtended() << std::endl;
}



json Camera::toJson() const
{
    json propertiesJson;

}



