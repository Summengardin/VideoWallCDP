#ifndef VIDEOWALLLIB_HANDCONTROLLEREASY_H
#define VIDEOWALLLIB_HANDCONTROLLEREASY_H

#include <array>
#include <string>
#include <CDPSystem/Base/CDPConnector.h>

namespace VideoWallLib {

class HandController {
    public:
        HandController();
        char buffer[1024];
        bool busy = false;
        int colorV = 0;
        MessageTextCommand txtMessage;
        // Parsing entry point

        // Button operations
        void toggleButton(int id);
        bool getButtonState(int id) const;

        // Joystick operations
        void setJoystick(int id, int value);
        int getJoystickState(int id) const;

        // Encoder operations
        void setEncoder(int id, int value);
        int getEncoderState(int id) const;

        std::array<bool, 6> buttons;     // id 1–6
        std::array<int, 3> joysticks;    // id 7–9
        std::array<int, 2> encoders;     // id 10–11

        std::string updateButtons(std::string outputline);
        std::string updateJoystick(std::string outputline);
        std::string updateEnc(std::string outputline, std::vector<std::string> tileMap);

    };
} // namespace VideoWallLib

#endif // VIDEOWALLLIB_HANDCONTROLLEREASY_H
