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
    i_GangwayLoad.Create("GangwayLoad",this);
    i_CraneLoad.Create("CraneLoad",this);
    i_Mode.Create("Mode",this);
    i_ShowOSDDescription.Create("ShowOSDDescription",this);
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
    index_inputs();
    /* Write your code here */
    for (auto p : m_osdports){
        int idx = p->TextIndex;
        p->TextProp = indexed_data[idx];
        if(DebugLevel(DEBUGLEVEL_EXTENDED))
            CDPMessage("Writing text prop (index=data) %f = %s \n", idx, indexed_data[idx].c_str());
    }
}

template <typename T>
std::string toString(T val){
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

void OSDDataDistributor::index_inputs(){

    if (i_ShowOSDDescription)
    {
        indexed_data[0] = "";
        indexed_data[1] = i_GangwayLoad.GetProperty("ShortName") + ": " + i_GangwayLoad.GetProperty("Description");
        indexed_data[2] = i_CraneLoad.GetProperty("ShortName") + ": " + i_CraneLoad.GetProperty("Description");
        indexed_data[3] = i_Mode.GetProperty("ShortName") + ": " + i_Mode.GetProperty("Description");
    }
    else{
        indexed_data[0] = "";
        indexed_data[1] = toString(i_GangwayLoad.GetDouble()) + " " + i_GangwayLoad.GetProperty("Unit");
        indexed_data[2] = toString(i_CraneLoad.GetDouble()) + " " + i_CraneLoad.GetProperty("Unit");
        indexed_data[3] = i_Mode + " " + i_Mode.GetProperty("Unit");
    }


    CDPMessage("Indexed data is:   ");
    for (auto d :   indexed_data)
        std::cout << d;
    std::cout << std::endl;
}


