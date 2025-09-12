#include "CameraMotionReferenceCalculation.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::CameraMotionReferenceCalculation
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for CameraMotionReferenceCalculation here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
CameraMotionReferenceCalculation::CameraMotionReferenceCalculation()
{
}

/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
CameraMotionReferenceCalculation::~CameraMotionReferenceCalculation()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void CameraMotionReferenceCalculation::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    Out.Create("Out",this);
    Position.Create("Position",this);
    TileUpdater.Create("TileUpdater",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void CameraMotionReferenceCalculation::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null",
                         (CDPCOMPONENT_STATEPROCESS) &CameraMotionReferenceCalculation::ProcessNull,
                         "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void CameraMotionReferenceCalculation::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
    TileUpdater.ConnectTo("VWController.VisionControllers.VisionController0.Tile01");
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
void CameraMotionReferenceCalculation::ProcessNull()
{
    double x_new = Position.GetPosition()->x;
    double y_new = Position.GetPosition()->y;
    double z_new = Position.GetPosition()->z - (0.5);
    Out.tilt_ref = atan2(z_new, sqrt(x_new*x_new+y_new*y_new));
    Out.pan_ref = atan2(y_new,x_new);
    MessageTextCommand txtMessage;
    MessagePacketHandle Outputmsg;
    txtMessage.SetTextCommand("MessageHandler");
    Outputmsg = txtMessage;
    std::string outputline = "Pan_abs: " + std::to_string(Out.pan_ref*180/M_PI)
                             + "; Tilt_abs: " + std::to_string(Out.tilt_ref*180/M_PI);
    outputline += +";\n";
    Outputmsg.Packet().PayloadAppend(outputline);
    TileUpdater.SendMessage(Outputmsg);

    /* Write your code here */
}
