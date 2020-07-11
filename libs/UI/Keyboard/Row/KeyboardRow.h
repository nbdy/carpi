//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_KEYBOARDROW_H
#define CARPI_KEYBOARDROW_H


#include <vector>
#include <tuple>
#include "../Key/Key.h"

class KeyboardRow {  // todo fix placement of row0
public:
    std::vector<Key*> row = {};

    KeyboardRow();

    std::tuple<float, float> getAverageSize();
    float getAverageSizeX();
    float getAverageSizeY();
    std::string _draw(float x, float y);
    std::string draw(float x, float y);
};

class KeyboardRow0 : public KeyboardRow {
public:
    KeyboardRow0(){
        row = {new KeyLeftStrg(), new KeyHome(), new KeyAlt(), new KeySpace(), new KeyAltGr(), new KeyContextMenu(), new KeyRightStrg(), new KeyHide()};
    }
};

class KeyboardRow1 : public KeyboardRow {
public:
    KeyboardRow1(){
        row = {new KeyLeftShift(), new KeyWeirdThingy0(), new KeyY(), new KeyX(), new KeyC(), new KeyV(), new KeyB(), new KeyN(), new KeyM(), new KeyComma(), new KeyDot(), new KeyMinus(), new KeyRightShift()};
    }
};

class KeyboardRow2 : public KeyboardRow {
public:
    KeyboardRow2(){
        row = {new KeyCapsLock(), new KeyA(), new KeyS(), new KeyD(), new KeyF(), new KeyG(), new KeyH(), new KeyJ(), new KeyK(), new KeyL(), new KeyHashtag(), new KeyEnter(), new KeyLeft(), new KeyDown(), new KeyRight()};
    }
};

class KeyboardRow3 : public KeyboardRow {
public:
    KeyboardRow3(){
        row = {new KeyTab(), new KeyQ(), new KeyW(), new KeyE(), new KeyR(), new KeyT(), new KeyZ(), new KeyU(), new KeyI(), new KeyO(), new KeyP(), new KeyPlus(), new KeySpacer(64), new KeyUp()};
    }
};

class KeyboardRow4 : public KeyboardRow {
public:
    KeyboardRow4(){
        row = {new KeyWeirdThingy1(), new Key1(), new Key2(), new Key3(), new Key4(), new Key5(), new Key6(), new Key7(), new Key8(), new Key9(), new Key0(), new KeySS(), new KeyHighComma(), new KeyBackspace()};
    }
};


#endif //CARPI_KEYBOARDROW_H
