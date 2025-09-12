/**
VideoWallLib header file. Include this file in the project to use the library.
*/

#ifndef VIDEOWALLLIB_VIDEOWALLLIB_H
#define VIDEOWALLLIB_VIDEOWALLLIB_H


#include "VideoWallLibBuilder.h"
#include <kinematics.h>
#include <mqttio.h>
#include <operationutilities.h>
#include <sequencer.h>
#include <videowalllib.h>

namespace VideoWallLib {

/** Instantiate the VideoWallLibBuilder for this object */
VideoWallLibBuilder gVideoWallLibBuilder("VideoWallLib");

}

#endif
