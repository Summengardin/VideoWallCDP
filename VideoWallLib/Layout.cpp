#include "Layout.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::Layout
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for Layout here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
Layout::Layout()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
Layout::~Layout()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void Layout::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    pLayout.Create("pLayout",this);
    Source01.Create("Source01",this);
    Source02.Create("Source02",this);
    Source03.Create("Source03",this);
    Source04.Create("Source04",this);
    Source11.Create("Source11",this);
    Source12.Create("Source12",this);
    Source13.Create("Source13",this);
    Source14.Create("Source14",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void Layout::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&Layout::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void Layout::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
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
void Layout::ProcessNull()
{
    pLayout.Source01 = Source01;
    pLayout.Source02 = Source02;
    pLayout.Source03 = Source03;
    pLayout.Source04 = Source04;
    pLayout.Source11 = Source11;
    pLayout.Source12 = Source12;
    pLayout.Source13 = Source13;
    pLayout.Source14 = Source14;
}
