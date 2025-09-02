#include "handControllerEasy.h"
namespace VideoWallLib {
    HandController::HandController(){
        buttons.fill(false);
        joysticks.fill(0);
        encoders.fill(0);
        colorV = 128;

    };


    void HandController::toggleButton(int id) {
        if (id >= 1 && id <= 6) {
            buttons[id - 1] = !buttons[id - 1];
        }
    }

    bool HandController::getButtonState(int id) const {
        if (id >= 1 && id <= 6) {
            return buttons[id - 1];
        }
        return false;
    }

    void HandController::setJoystick(int id, int value) {
        if (id >= 7 && id <= 9) {
            joysticks[id - 7] = value;
        }
    }

    int HandController::getJoystickState(int id) const {
        if (id >= 7 && id <= 9) {
            return joysticks[id - 7];
        }
        return 0;
    }

    void HandController::setEncoder(int id, int value) {
        if (id >= 10 && id <= 11) {
            encoders[id - 10] = value;
        }
    }

    int HandController::getEncoderState(int id) const {
        if (id >= 10 && id <= 11) {
            return encoders[id - 10];
        }
        return 0;
    }

    std::string HandController::updateButtons(std::string outputline){
        for (int a = 1; a < 7; a++) {
            if (buttons[a-1]){
                outputline += "HWC#" + std::to_string(a) + "=36\n";
                outputline += "HWCc#" + std::to_string(a) + "=" + std::to_string(130 | 0x80) + "\n";
                outputline += "HWCt#" + std::to_string(a) + "=" + std::string("Pressed") + "\n";
            } else {

                outputline += "HWC#" + std::to_string(a) + "=5\n";
                outputline += "HWCc#" + std::to_string(a) + "=" + std::to_string(130 | 0x80) + "\n";
                outputline += "HWCt#" + std::to_string(a) + "=" + std::string("") + "\n";
            }
         }
        return outputline;
    }

    std::string HandController::updateJoystick(std::string outputline){
        for (int a = 7; a < 10; a++) {
            outputline += "HWC#" + std::to_string(a) + "=5\n";
            outputline += "HWCc#" + std::to_string(a) + "=" + std::to_string(130 | 0x80) + "\n";
         }
        return outputline;
    }

    std::string HandController::updateEnc(std::string outputline){
        // Need to find out what type of update you want on the encoder
        for (int a = 10; a < 12; a++) {
            outputline += "HWC#" + std::to_string(a) + "=5\n";
            outputline += "HWCc#" + std::to_string(a) + "=" + std::to_string(130 | 0x80) + "\n";
            outputline += "HWCt#" + std::to_string(a) + "=" + std::to_string(encoders[a-10]) + "\n";

         }
        return outputline;
    }

} // namespace MQTTTest

