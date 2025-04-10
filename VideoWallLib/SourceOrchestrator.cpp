#include "SourceOrchestrator.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::SourceOrchestrator
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for SourceOrchestrator here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
SourceOrchestrator::SourceOrchestrator()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
SourceOrchestrator::~SourceOrchestrator()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void SourceOrchestrator::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    pLayout.Create("pLayout",this);
    S01.Create("S01",this);
    S02.Create("S02",this);
    S03.Create("S03",this);
    S04.Create("S04",this);
    S11.Create("S11",this);
    S12.Create("S12",this);
    S13.Create("S13",this);
    S14.Create("S14",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void SourceOrchestrator::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&SourceOrchestrator::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void SourceOrchestrator::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);

    for (CDPPort* port : m_ports){
        if (CameraPort* camera = dynamic_cast<CameraPort*>(port))
            cameraPorts.push_back(camera);
    }
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
void SourceOrchestrator::ProcessNull()
{
  S01 = pLayout.Source01;
  S02 = pLayout.Source02;
  S03 = pLayout.Source03;
  S04 = pLayout.Source04;
  S11 = pLayout.Source11;
  S12 = pLayout.Source12;
  S13 = pLayout.Source13;
  S14 = pLayout.Source14;

}
