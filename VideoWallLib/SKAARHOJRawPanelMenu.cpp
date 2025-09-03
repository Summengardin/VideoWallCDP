#include "SKAARHOJRawPanelMenu.h"
#include <OSAPI/Process/OSAPISemaphore.h>
using namespace VideoWallLib;

/*!
  \class VideoWallLib::SKAARHOJRawPanelMenu
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for SKAARHOJRawPanelMenu here.
*/

SKAARHOJRawPanelMenu::SKAARHOJRawPanelMenu() {
}

SKAARHOJRawPanelMenu::~SKAARHOJRawPanelMenu() {
}

void SKAARHOJRawPanelMenu::Create(const char *fullName) {
  CDPComponent::Create(fullName);

  m_counter.Create("Counter", this);// Example signal counted by both main thread and state-machine
  ToIO.Create("ToIO",this);
}

void SKAARHOJRawPanelMenu::CreateModel() {
  CDPComponent::CreateModel();

  RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS) &SKAARHOJRawPanelMenu::ProcessNull, "Initial Null state");
  RegisterMessage(CM_TEXTCOMMAND,"FromIO","",(CDPOBJECT_MESSAGEHANDLER)&SKAARHOJRawPanelMenu::MessageFromIO);
}

void SKAARHOJRawPanelMenu::Configure(const char *componentXML) {
  CDPComponent::Configure(componentXML);
}

void SKAARHOJRawPanelMenu::ProcessNull() {
  m_event.Set();// this triggers the main thread
  m_counter += 10;
}



int SKAARHOJRawPanelMenu::MessageFromIO(void* message)
{
  return 1;

}

void SKAARHOJRawPanelMenu::Activate() {
  CDPComponent::Activate();
  // Start the Main() thread with name of the component and normal priority:
  Start(CDPTHREAD_PRIORITY_NORMAL, ShortName());
}

void SKAARHOJRawPanelMenu::Suspend() {
  CDPComponent::Suspend();
  Stop();       // set Stop flag
  m_event.Set();// set event so that Wait in Main() completes.
  Delete();     // will block until thread is no longer running (for max. 2 seconds)
}

/*!
  \internal
  \brief Main thread function, runs asynchronously from state-machine.

  Note that it is not safe to access cdp signals, parameters, alarms etc. from a thread.
  The helper RunInComponentThread() and the component member access mutex ( GetMemberAccessMutex() )
  can be used to safely access cdp objects. As in the process functions, any timeconsuming processing
  performed while the member access mutex is locked may impact the scheduling of other components running
  at the same priority as this component.
*/
void SKAARHOJRawPanelMenu::Main() {
  while (!Stopped()) {
    m_event.Wait();
    m_event.Reset();
    if (!Stopped()) {
      CDPMessage("%s::Main() was triggered\n", CDPComponent::Name());

      AccessObjectsUsingMemberAccessMutex();

      // TODO: Put (lengthy/blocking) code here that should run whenever you do 'm_event.Set()'
      OSAPISleep(5 * 1000.0 * ts);// simulate lengthy processing by sleeping five periods...

      AccessObjectsBySchedulingIntoComponentThread();
    }
  }
}

/*!
  \internal
  \brief Shows how to safely access cdp objects using the memberaccess mutex
*/
void SKAARHOJRawPanelMenu::AccessObjectsUsingMemberAccessMutex() {
  OSAPIMutexLocker locker(GetMemberAccessMutex(), "Main thread member access");// automatic unlock when object is destroyed
  m_counter += 20;                                                             // It is now safe to access variables, but note that locking the mutex will block
                                                                               // the component statemachine from running for the duration of the lock.
}

/*!
  \internal
  \brief Executes the toggling of m_toggleSignal the next time the component is run, after state-transitions and state run:
*/
void SKAARHOJRawPanelMenu::AccessObjectsBySchedulingIntoComponentThread() {
  RunInComponentThread([&]() {
    m_counter += 70;
  });
}
