#include "skhojhandcontroller.h"
#include <iostream>
#include <regex>
#include <thread>
#include <chrono>
#include <mutex>
#include "base64.h"

// HWCComponent implementations
SKHOJ::HWCComponent::HWCComponent(int id, Callback cb)
    : hwc_id(id), callback(cb), color(HWCColor::DEFAULT_COLOR), has_display(false) {}

void SKHOJ::HWCComponent::setColor(HWCColor c) {
    color = c;
}

void SKHOJ::HWCComponent::setColorRGB(int r, int g, int b) {
    // Default no-op; override in subclasses if needed
}

void SKHOJ::HWCComponent::RunCallback(const std::string& event, const std::string& data) {
    if (callback) callback(hwc_id, event, data);
}

bool SKHOJ::HWCComponent::HasDisplay() { return has_display; }

int SKHOJ::HWCComponent::HwcID() { return hwc_id; }

// Button
void SKHOJ::Button::HandleCommand(const std::string& cmd, int mask) {
    if (cmd == "Down" || cmd == "Up" || cmd == "Press")
      RunCallback(cmd);
    else
      RunCallback("Unknown", cmd);
}

// DPad
SKHOJ::DPad::DPad(int id, Callback cb) : HWCComponent(id, cb) {
    has_display = true;
}

void SKHOJ::DPad::HandleCommand(const std::string& cmd, int mask) {
  static std::map<int, std::string> edgeMap {{1,"N"},{2,"W"},{4,"S"},{8,"E"}}; // Direction relative to button
    std::string edge = (mask >= 0 && edgeMap.count(mask)) ? edgeMap[mask] : "Unknown(" + std::to_string(mask) + ")";
    RunCallback(cmd, edge);
}

// TBar
void SKHOJ::TBar::HandleCommand(const std::string& cmd, int mask) {
    if (cmd.rfind("Abs:",0) == 0) {
    RunCallback("Abs", cmd.substr(4));
    } else {
      RunCallback("Unknown", cmd);
    }
}

// Encoder
void SKHOJ::Encoder::HandleCommand(const std::string& cmd, int mask) {
    if (cmd.rfind("Enc:",0) == 0) {
    RunCallback("Rotate", cmd.substr(4));
        // scheduleZeroState();
    } else if (cmd == "Press") {
      RunCallback("Press");
        // scheduleFalseState();
    } else {
      RunCallback("Unknown", cmd);
    }
}

void SKHOJ::Encoder::scheduleZeroState() {
    std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(encoder_timeout_ms));
    RunCallback("Rotate", "0");
    }).detach();
}

void SKHOJ::Encoder::scheduleFalseState() {
    std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(press_timeout_ms));
    RunCallback("Press", "0");
    }).detach();
}

// JoyStick
void SKHOJ::JoyStick::HandleCommand(const std::string& cmd, int mask) {
    if (cmd.rfind("Speed:",0) == 0)
      RunCallback("Speed", cmd.substr(6));
    else if (cmd == "Down" || cmd == "Up")
      RunCallback(cmd);
    else
      RunCallback("Unknown", cmd);
}

// HandController
SKHOJ::HandController::HandController(std::function<void(const std::string&)> sysCb, std::function<void(const std::string&)> senderCb)
    : system_callback(sysCb), sender(senderCb), ready(true), is_sleeping(false), sleep_timer(0) {}

void SKHOJ::HandController::RegisterComponent(std::shared_ptr<HWCComponent> comp) {
  components[comp->HwcID()] = comp;
}

void SKHOJ::HandController::HandleCommand(const std::string& raw) {
  if (raw.rfind("HWC#",0) == 0) HandleHwc(raw);
  else if (raw.rfind("map=",0) == 0) HandleMap(raw);
  else HandleSystem(raw);
}

void SKHOJ::HandController::Send(const std::string& cmd) {
    if (sender) sender(cmd + "\n");
    else std::cout << "[SEND] " << cmd << std::endl;
}

// ========== PANEL COMMANDS ==========
void SKHOJ::HandController::ack() { Send("ack"); }
void SKHOJ::HandController::clearAll() { Send("Clear"); }
void SKHOJ::HandController::clearLEDs() { Send("ClearLEDs"); }
void SKHOJ::HandController::clearDisplays() { Send("ClearDisplays"); }
void SKHOJ::HandController::reboot() { Send("Reboot"); }
void SKHOJ::HandController::activatePanel() { Send("ActivePanel=1"); }
void SKHOJ::HandController::requestInfo() { Send("list"); }
void SKHOJ::HandController::ping() { Send("ping"); }
void SKHOJ::HandController::requestMap() { Send("map"); }
void SKHOJ::HandController::requestTopology() { Send("PanelTopology?"); }
void SKHOJ::HandController::setSleepTimer(int ms) { Send("SleepTimer=" + std::to_string(ms)); }
void SKHOJ::HandController::getSleepTimer() { Send("SleepTimer?"); }
void SKHOJ::HandController::wakeUp() { Send("WakeUp!"); }

void SKHOJ::HandController::SetSystemCallback(std::function<void(const std::string&)> cb) {
    system_callback = std::move(cb);
}

void SKHOJ::HandController::SetSenderCallback(std::function<void(const std::string&)> cb) {
    sender = std::move(cb);
}


void SKHOJ::HandController::SetEncoderPressMode(int flags) { Send("encoderPressMode=" + std::to_string(flags)); }

void SKHOJ::HandController::SetPanelBrightness(int led, int oled) {
    led = std::clamp(led, 0, 8);
    if (oled >= 0) oled = std::clamp(oled, 0, 8);
    if (oled >= 0) Send("PanelBrightness="+std::to_string(led)+","+std::to_string(oled));
    else Send("PanelBrightness="+std::to_string(led));
}

void SKHOJ::HandController::SetPanelBrightnessPercent(int ledPct, int oledPct) {
    int led = ledPct * 8 / 100;
    int oled = oledPct>=0 ? oledPct * 8 / 100 : -1;
    SetPanelBrightness(led, oled);
}

void SKHOJ::HandController::toggleWebserver(bool on) { Send(std::string("Webserver=") + (on?"1":"0")); }

void SKHOJ::HandController::setColor(int id, HWCColor color) {
    auto it = components.find(id);
    if (it != components.end()) {
      it->second->setColor(color);
      Send("HWCc#"+std::to_string(id)+"="+std::to_string(static_cast<int>(color)));
    }
    else std::cerr<<"[ERROR] HWC#"<<id<<" not registered\n";
}

void SKHOJ::HandController::setColorRGB(int id, int r, int g, int b) {
    auto it = components.find(id);
    if (it != components.end()) it->second->setColorRGB(r,g,b);
    else std::cerr<<"[ERROR] HWC#"<<id<<" not registered\n";
}

void SKHOJ::HandController::setColorAll(HWCColor color) { for(auto& kv:components) setColor(kv.first,color); }
void SKHOJ::HandController::setColorRGBAll(int r, int g, int b) { for(auto& kv:components) kv.second->setColorRGB(r,g,b); Send("SetColorRGB="+std::to_string(r)+","+std::to_string(g)+","+std::to_string(b)); }

void SKHOJ::HandController::setHwcState(int id, HWCState state) {
    auto it = components.find(id);
    if (it != components.end())
      Send( "HWC#" + std::to_string(id) + "=" + std::to_string(static_cast<int>(state)) );
    else
      std::cerr<<"[ERROR] HWC#"<<id<<" not registered\n";
}
void SKHOJ::HandController::setHwcStateAll(HWCState state) { for(auto& kv:components) setHwcState(kv.first,state); }

void SKHOJ::HandController::setDisplayText(int id, int value, int format, int fne, const std::string& title,
                                    bool isLabel, const std::string& label1, const std::string& label2,
                                    int value2, int valuesPair, int scale,
                                    int scaleRangeLow, int scaleRangeHigh,
                                    int scaleLimitLow, int scaleLimitHigh,
                                    int img, int font,
                                    const std::string& fontSize,
                                    const std::string& advanced) {
    auto it = components.find(id);
  if (it==components.end()) {
        std::cerr<<"[ERROR] HWC#"<<id<<" not registered\n";
        return;
    }
  else if (!it->second->HasDisplay()) {
      std::cerr<<"[ERROR] HWC#"<<id<<" has no display\n";
      return;
    }
    std::ostringstream oss;
    // build tokens
    std::vector<std::string> tokens = {
        value>=0?std::to_string(value):"",
        format>=0?std::to_string(format):"",
        fne>=0?std::to_string(fne):"",
        title.substr(0,10),
        isLabel?"1":"0",
        label1.substr(0,25),
        label2,
        value2>=0?std::to_string(value2):"",
        valuesPair>=0?std::to_string(valuesPair):"",
        scale>=0?std::to_string(scale):"",
        scaleRangeLow>=0?std::to_string(scaleRangeLow):"",
        scaleRangeHigh>=0?std::to_string(scaleRangeHigh):"",
        scaleLimitLow>=0?std::to_string(scaleLimitLow):"",
        scaleLimitHigh>=0?std::to_string(scaleLimitHigh):"",
        img>=0?std::to_string(img):"",
        font>=0?std::to_string(font):"",
        fontSize,
        advanced
    };
    std::string joined;
    for(size_t i=0;i<tokens.size();++i) {
        if(i) joined += "|";
        joined += tokens[i];
    }
    joined = joined.substr(0,63);
    Send("HWCt#"+std::to_string(id)+"="+joined);
}

void SKHOJ::HandController::setDisplayTextAll(int value, int format, int fne, const std::string& title,
                                       bool isLabel, const std::string& label1, const std::string& label2,
                                       int value2, int valuesPair, int scale,
                                       int scaleRangeLow, int scaleRangeHigh,
                                       int scaleLimitLow, int scaleLimitHigh,
                                       int img, int font,
                                       const std::string& fontSize,
                                       const std::string& advanced) {
    for(auto& kv:components) setDisplayText(kv.first,value,format,fne,title,isLabel,label1,label2,value2,valuesPair,scale,scaleRangeLow,scaleRangeHigh,scaleLimitLow,scaleLimitHigh,img,font,fontSize,advanced);
}

void SKHOJ::HandController::setDisplayGraphicsFromEnum(int id, HWCGraphics graphics) {
    // placeholder for actual graphics data lookup
}

void SKHOJ::HandController::setDisplayGraphics(int id, const std::vector<uint8_t>& imageData, int cacheId) {
    auto it = components.find(id);
    if(it==components.end() || !it->second->HasDisplay()) { std::cerr<<"[ERROR] HWC#"<<id<<" not registered/display\n"; return; }
    size_t len = imageData.size();
    if(len!=256) { std::cerr<<"[ERROR] Image must be 256 bytes, got "<<len<<"\n"; return; }
    if(cacheId>0) Send("HWCg#"+std::to_string(id)+"={CS:"+std::to_string(cacheId)+"}");
    for(int part=0; part<3; ++part) {
        auto begin = imageData.begin()+part*86;
        auto end = (part<2? begin+86: imageData.end());
        std::string chunk(begin, end);
        std::string b64 = base64_encode(reinterpret_cast<const unsigned char*>(chunk.data()), chunk.size());
        Send("HWCg#"+std::to_string(id)+"="+std::to_string(part)+":"+b64);
    }
}

void SKHOJ::HandController::recallDisplayGraphics(int id, int cacheId) {
    if(cacheId<1 || cacheId>32767) { std::cerr<<"[ERROR] Invalid cacheId"<<"\n"; return; }
    Send("HWCg#"+std::to_string(id)+"={CR"+std::to_string(cacheId)+"}");
}

void SKHOJ::HandController::setDisplayGraphicsAll(const std::vector<uint8_t>& imageData, int cacheId) {
    for(auto& kv:components) setDisplayGraphics(kv.first,imageData,cacheId);
}

// Internal handlers
void SKHOJ::HandController::HandleHwc(const std::string& raw) {
    std::smatch m;
    if ( std::regex_match( raw,m,std::regex("HWC#(\\d+)(?:\\.(\\d+))?=(.+)") ) ) {
        int id = std::stoi(m[1]);
        int mask = m[2].matched?std::stoi(m[2]):-1;
        std::string cmd = m[3];
        if(components.count(id)) components[id]->HandleCommand(cmd,mask);
    }
}

void SKHOJ::HandController::HandleMap(const std::string& raw) {
    std::smatch m;
    if(std::regex_match(raw,m,std::regex("map=(\\d+):(\\d+)"))) {
      int nat = std::stoi(m[1]);
        int ext = std::stoi(m[2]);
        map_native_to_external[nat]=ext;
        map_external_to_native[ext].push_back(nat);
        if(system_callback) system_callback("map_update");
    }
}

void SKHOJ::HandController::HandleSystem(const std::string& raw) {
    // std::cout<<"[SYS] "<< raw <<"\n";
}
