#ifndef HANDCONTROLLER_H
#define HANDCONTROLLER_H

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <memory>

namespace SKHOJ {

// Enums for colors, formats, states, graphics
enum class HWCColor : uint8_t {
    DEFAULT_COLOR = 128, OFF = 129, WHITE = 130, WARM_WHITE = 131,
    RED = 132, ROSE = 133, PINK = 134, PURPLE = 135,
    AMBER = 136, YELLOW = 137, DARK_BLUE = 138,
    BLUE = 139, ICE = 140, CYAN = 141,
    SPRING = 142, GREEN = 143, MINT = 144
};

enum class HWCFormat : uint8_t {
    INTEGER = 0, FLOAT_10E3_2DP = 1, PERCENT = 2, DB = 3,
    FRAMES = 4, INVERSE = 5, KELVIN = 6, HIDDEN = 7,
    FLOAT_10E3_3DP = 8, FLOAT_10E2_2DP = 9,
    TEXTLINE_1 = 10, TEXTLINE_2 = 11
};

enum class HWCState : uint16_t {
    OFF = 0, ON_RED = 2, ON_GREEN = 3, ON_DEFAULT = 4,
    ON = 36, DIMMED = 5,
    BLINK_MONO = 1 << 4, OUTPUT_BIT = 1 << 5,
    BLINK_4HZ = 1 << 8, BLINK_0_5HZ = 1 << 11,
    BLINK_0_5HZ_75_DUTY = (1 << 11) | (1 << 10)
};

enum class HWCGraphics : uint8_t { NONE, CHECKERBOARD, GRADIENT, SOLID };


/*----  Base abstract component  ---*/
class HWCComponent {
public:
    using Callback = std::function<void(int, const std::string&, const std::string&)>;
    HWCComponent(int id, Callback cb = nullptr);
    virtual ~HWCComponent() = default;

    virtual void HandleCommand(const std::string& cmd, int mask = -1) = 0;
    virtual void setColor(HWCColor c);
    virtual void setColorRGB(int r, int g, int b);
    bool HasDisplay();
    int HwcID();

protected:
    int hwc_id;
    Callback callback;
    HWCColor color;
    bool has_display;

    void RunCallback(const std::string& event, const std::string& data = "");
};


/*----  Derived components  ----*/
class Button : public HWCComponent {
public:
    using HWCComponent::HWCComponent;
  void HandleCommand(const std::string& cmd, int mask = -1) override;
};

class DPad : public HWCComponent {
public:
    DPad(int id, Callback cb = nullptr);
  void HandleCommand(const std::string& cmd, int mask = -1) override;
};

class TBar : public HWCComponent {
public:
    using HWCComponent::HWCComponent;
  void HandleCommand(const std::string& cmd, int mask = -1) override;
};

class Encoder : public HWCComponent {
public:
    using HWCComponent::HWCComponent;
  void HandleCommand(const std::string& cmd, int mask = -1) override;

private:
    void scheduleZeroState();
    void scheduleFalseState();
    int encoder_timeout_ms;
    int press_timeout_ms;
};

class JoyStick : public HWCComponent {
public:
    using HWCComponent::HWCComponent;
  void HandleCommand(const std::string& cmd, int mask = -1) override;
};


/*---- HandController manages components and communication  ----*/
class HandController {
public:
    using Callback = HWCComponent::Callback;
    HandController(std::function<void(const std::string&)> sysCb = nullptr, std::function<void(const std::string&)> senderCb = nullptr);
    void RegisterComponent(std::shared_ptr<HWCComponent> comp);
    void HandleCommand(const std::string& raw);
    void Send(const std::string& cmd);

    void ack();
    void clearAll();
    void clearLEDs();
    void clearDisplays();
    void reboot();
    void activatePanel();
    void requestInfo();
    void ping();
    void requestMap();
    void requestTopology();
    void setSleepTimer(int ms);
    void getSleepTimer();
    void wakeUp();

    void SetSystemCallback( std::function<void(const std::string&)> sysCb );
    void SetSenderCallback( std::function<void(const std::string&)> sender );

    void SetEncoderPressMode(int flags);
    void SetPanelBrightness(int led, int oled = -1);
    void SetPanelBrightnessPercent(int ledPct, int oledPct = -1);
    void toggleWebserver(bool on);
    void setColor(int hwc_id, HWCColor color);
    void setColorRGB(int hwc_id, int r, int g, int b);
    void setColorAll(HWCColor color);
    void setColorRGBAll(int r, int g, int b);
    void setHwcState(int hwc_id, HWCState state);
    void setHwcStateAll(HWCState state);
    void setDisplayText(int hwc_id,
                        int value = -1,
                        int format = -1,
                        int fne = -1,
                        const std::string& title = "",
                        bool isLabel = false,
                        const std::string& label1 = "",
                        const std::string& label2 = "",
                        int value2 = -1,
                        int valuesPair = -1,
                        int scale = -1,
                        int scaleRangeLow = -1,
                        int scaleRangeHigh = -1,
                        int scaleLimitLow = -1,
                        int scaleLimitHigh = -1,
                        int img = -1,
                        int font = -1,
                        const std::string& fontSize = "",
                        const std::string& advanced = "");
    void setDisplayTextAll(int value = -1,
                           int format = -1,
                           int fne = -1,
                           const std::string& title = "",
                           bool isLabel = false,
                           const std::string& label1 = "",
                           const std::string& label2 = "",
                           int value2 = -1,
                           int valuesPair = -1,
                           int scale = -1,
                           int scaleRangeLow = -1,
                           int scaleRangeHigh = -1,
                           int scaleLimitLow = -1,
                           int scaleLimitHigh = -1,
                           int img = -1,
                           int font = -1,
                           const std::string& fontSize = "",
                           const std::string& advanced = "");
    void setDisplayGraphicsFromEnum(int hwc_id, HWCGraphics graphics);
    void setDisplayGraphics(int hwc_id, const std::vector<uint8_t>& imageData, int cacheId = -1);
    void recallDisplayGraphics(int hwc_id, int cacheId);
    void setDisplayGraphicsAll(const std::vector<uint8_t>& imageData, int cacheId = -1);

private:
    std::map<int, std::shared_ptr<HWCComponent>> components;
    std::map<int,int> map_native_to_external;
    std::map<int,std::vector<int>> map_external_to_native;
    std::function<void(const std::string&)> system_callback, sender;
    bool ready;
    bool is_sleeping;
    std::string serial, model, version;
    std::map<int,std::string> state_registers;
    std::map<int,std::string> shift_registers;
    int sleep_timer;

    void HandleHwc(const std::string& raw);
    void HandleMap(const std::string& raw);
    void HandleSystem(const std::string& raw);
};

} // namespace SKHOJ

#endif // HANDCONTROLLER_H
