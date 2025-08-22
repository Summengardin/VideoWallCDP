#include "OSDDataDistributor.h"

using namespace VideoWallLib;
/*!
  \class VideoWallLib::OSDDataDistributor
  \inmodule VideoWallLib

  \section1 Usage

  Add documentation for OSDDataDistributor here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
OSDDataDistributor::OSDDataDistributor()
{
}

/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
OSDDataDistributor::~OSDDataDistributor()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void OSDDataDistributor::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    i_Mode.Create("Mode",this);
    i_ShowOSDDescription.Create("ShowOSDDescription",this);
    CraneLoad.Create("CraneLoad",this);
    GangwayLoad.Create("GangwayLoad",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void OSDDataDistributor::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS) &OSDDataDistributor::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void OSDDataDistributor::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);

    for (auto p : m_ports)
        if (OSDPort* osd_port = dynamic_cast<OSDPort*>(p))
            m_osdports.push_back(osd_port);


    indexed_data.resize(m_listSignals.size()); // Yes, this will make it bigger than necessary - quick and dirty
    prevTimeouts.resize(m_listSignals.size());
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
void OSDDataDistributor::ProcessNull()
{
    IndexInputs();

    for (size_t i = 0; i < m_osdports.size(); i++){
        auto p = m_osdports[i];
        try {
            p->Text = indexed_data.at(p->TextIndex);
            if (!i_ShowOSDDescription)
                prevTimeouts[i] = p->Timeout;
        } catch (const std::out_of_range& e) {
            CDPMessage("%s: Index %i out of range for OSD Data selection\n", e.what(), p->TextIndex.c_str());
        }
        if(DebugLevel(DEBUGLEVEL_EXTENDED))
            CDPMessage("Writing text prop (index=data) %f = %s \n", p->TextIndex.c_str(), indexed_data[p->TextIndex].c_str());
    }
}


void OSDDataDistributor::IndexInputs(){

    int string_cnt = 0;
    for (ICDPSignal* signal : m_listSignals) {
        // Get the value as a generic variant or base type
        if  (CDPSignal<std::string>* value = dynamic_cast<CDPSignal<std::string>*>(signal) ){
            if (i_ShowOSDDescription)
                indexed_data[string_cnt++] =  value->GetProperty("ShortName") + " [" + value->GetProperty("Unit") + "]: " + value->GetProperty("Description");
            else
                indexed_data[string_cnt++] = value->GetRawValue();

            if (DebugLevel(DEBUGLEVEL_EXTENDED))
                std::cout << "String value: " << value->GetRawValue() << " | DESC: " << value->GetProperty("ShortName") + " [" + value->GetProperty("Unit") + "]: " + value->GetProperty("Description") << std::endl;
        }
    }
}


