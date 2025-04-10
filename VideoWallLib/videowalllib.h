/**
VideoWallLib header file. Include this file in the project to use the library.
*/

#ifndef VIDEOWALLLIB_VIDEOWALLLIB_H
#define VIDEOWALLLIB_VIDEOWALLLIB_H


#include "VideoWallLibBuilder.h"
#include <mqttio.h>
#include <sequencer.h>

namespace VideoWallLib {

/** Instantiate the VideoWallLibBuilder for this object */
VideoWallLibBuilder gVideoWallLibBuilder("VideoWallLib");

}

#endif
