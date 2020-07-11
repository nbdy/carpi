//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_KEY_H
#define CARPI_KEY_H

#include <string>
#include <raylib.h>

class Key {
public:
    std::string key;
    float sizeY = 42;
    float sizeX = 42;
    std::string value;

    Key();

    bool draw(float x, float y);
    bool isPressed(const std::string& data);

    static bool isPressed(const std::string& data, const std::string& keyValue){
        return data.find(keyValue) != std::string::npos;
    }
};

class KeyLeftStrg : public Key {
public:
    KeyLeftStrg(){
        key = "strg";
        sizeX = 64;
        value = "{{{strg}}}";
    }
};

class KeyHome : public Key {
public:
    KeyHome(){
        key = "home";
        sizeX = 42;
        value = ""; // todo whats the value of this?
    }
};

class KeyAlt : public Key {
public:
    KeyAlt(){
        key = "alt";
        sizeX = 64;
        value = ""; // todo whats the value of this?
    }
};

class KeySpace : public Key {
public:
    KeySpace(){
        key = "__________";
        value = " ";
        sizeX = 320;
    }
};

class KeyAltGr : public Key {
public:
    KeyAltGr(){
        key = "alt gr";
        value = ""; // todo whats the value of this?
        sizeX = 64;
    }
};

class KeyContextMenu : public Key {
public:
    KeyContextMenu(){
        key = "[=]";
        value = "{{{ctxmenu}}}";
        sizeX = 42;
    }
};

class KeyRightStrg : public Key {
public:
    KeyRightStrg(){
        key = "strg";
        value = ""; // todo
        sizeX = 64;
    }
};

class KeyLeftShift : public Key {
public:
    KeyLeftShift(){
        key = "/\\";
        value = ""; // todo;
        sizeX = 64;
    }
};

class KeyWeirdThingy0 : public Key {
public:
    KeyWeirdThingy0(){
        key = "<";
        value = key;
    }
};

class KeyY : public Key {
public:
    KeyY(){
        key = "y";
        value = key;
    }
};

class KeyX : public Key {
public:
    KeyX(){
        key = "x";
        value = key;
    }
};

class KeyC : public Key {
public:
    KeyC() {
        key = "c";
        value = key;
    }
};

class KeyV : public Key {
public:
    KeyV() {
        key = "v";
        value = key;
    }
};

class KeyB : public Key {
public:
    KeyB(){
        key = "b";
        value = key;
    }
};

class KeyN : public Key {
public:
    KeyN() {
        key = "n";
        value = key;
    }
};

class KeyM : public Key {
public:
    KeyM(){
        key = "m";
        value = key;
    }
};

class KeyComma : public Key {
public:
    KeyComma(){
        key = ",";
        value = key;
    }
};

class KeyDot : public Key {
public:
    KeyDot(){
        key = ".";
        value = key;
    }
};

class KeyMinus : public Key {
public:
    KeyMinus() {
        key = "-";
        value = key;
    }
};

class KeyRightShift : public Key {
public:
    KeyRightShift() {
        key = "/\\";
        value = "{{{shift}}}";
        sizeX = 178;
    }
};

class KeyCapsLock : public Key {
public:
    KeyCapsLock(){
        key = "caps";
        value = "{{{caps}}}";
        sizeX = 64;
    }
};

class KeyA : public Key {
public:
    KeyA(){
        key = "a";
        value = key;
    }
};

class KeyS : public Key {
public:
    KeyS(){
        key = "s";
        value = key;
    }
};

class KeyD : public Key {
public:
    KeyD(){
        key = "d";
        value = key;
    }
};

class KeyF : public Key {
public:
    KeyF(){
        key = "f";
        value = key;
    }
};

class KeyG : public Key {
public:
    KeyG(){
        key = "g";
        value = key;
    }
};

class KeyH : public Key {
public:
    KeyH(){
        key = "h";
        value = key;
    }
};

class KeyJ : public Key {
public:
    KeyJ(){
        key = "j";
        value = key;
    }
};

class KeyK : public Key {
public:
    KeyK(){
        key = "k";
        value = key;
    }
};

class KeyL : public Key {
public:
    KeyL(){
        key = "l";
        value = key;
    }
};

class KeyHashtag : public Key {
public:
    KeyHashtag(){
        key = "#";
        value = key;
    }
};

class KeyEnter : public Key {
public:
    KeyEnter(){
        key = "enter";
        value = "\n";
        sizeX = 64;
    }
};

class KeyTab : public Key {
public:
    KeyTab(){
        key = "tab";
        sizeX = 64;
        value = "\t";
    }
};

class KeyQ : public Key {
public:
    KeyQ(){
        key = "q";
        value = key;
    }
};

class KeyW : public Key {
public:
    KeyW(){
        key = "w";
        value = key;
    }
};

class KeyE : public Key {
public:
    KeyE(){
        key = "e";
        value = key;
    }
};

class KeyR : public Key {
public:
    KeyR(){
        key = "r";
        value = key;
    }
};

class KeyT : public Key {
public:
    KeyT(){
        key = "t";
        value = key;
    }
};

class KeyZ : public Key {
public:
    KeyZ() {
        key = "z";
        value = key;
    }
};

class KeyU : public Key {
public:
    KeyU(){
        key = "u";
        value = key;
    }
};

class KeyI : public Key {
public:
    KeyI(){
        key = "i";
        value = key;
    }
};

class KeyO : public Key {
public:
    KeyO(){
        key = "o";
        value = key;
    }
};

class KeyP : public Key {
public:
    KeyP(){
        key = "p";
        value = key;
    }
};

class KeyPlus : public Key{
public:
    KeyPlus(){
        key = "+";
        value = key;
    }
};

class KeyWeirdThingy1 : public Key {
public:
    KeyWeirdThingy1() {
        key = ""; // todo
        value = key;
    }
};

class Key1 : public Key {
public:
    Key1(){
        key = "1";
        value = key;
    }
};

class Key2 : public Key {
public:
    Key2(){
        key = "2";
        value = key;
    }
};

class Key3 : public Key {
public:
    Key3(){
        key = "3";
        value = key;
    }
};

class Key4 : public Key {
public:
    Key4(){
        key = "4";
        value = key;
    }
};

class Key5 : public Key {
public:
    Key5(){
        key = "5";
        value = key;
    }
};

class Key6 : public Key {
public:
    Key6(){
        key = "6";
        value = key;
    }
};

class Key7 : public Key {
public:
    Key7(){
        key = "7";
        value = key;
    }
};

class Key8 : public Key {
public:
    Key8(){
        key = "8";
        value = key;
    }
};

class Key9 : public Key {
public:
    Key9(){
        key = "9";
        value = key;
    }
};

class Key0 : public Key {
public:
    Key0(){
        key = "0";
        value = key;
    }
};

class KeySS : public Key {
public:
    KeySS(){
        key = "ß";
        value = key;
    }
};

class KeyHighComma : public Key {
public:
    KeyHighComma(){
        key = ""; // todo
        value = key;
    }
};

class KeyBackspace : public Key {
public:
    KeyBackspace(){
        key = "<<<";
        value = "{{{backspace}}}";
        sizeX = 84;
    }
    static bool isPressed(const std::string& data){return Key::isPressed(data, "{{{backspace}}}");}
};

class KeyHide : public Key {
public:
    KeyHide(){
        key = "\\/";
        value = "{{{hide}}}";
        sizeX = 64;
    }
    static bool isPressed(const std::string& data){return Key::isPressed(data, "{{{hide}}}");}
};

class KeyLeft : public Key {
public:
    KeyLeft(){
        key = "<<";
        value = "{{{left}}}";
    }
    static bool isPressed(const std::string& data){return Key::isPressed(data, "{{{left}}}");}
};

class KeyDown : public Key {
public:
    KeyDown() {
        key = "\\/";
        value = "{{{down}}}";
    }
    static bool isPressed(const std::string& data){return Key::isPressed(data, "{{{down}}}");}
};

class KeyUp : public Key {
public:
    KeyUp(){
        key = "/\\";
        value = "{{{up}}}";
    }
    static bool isPressed(const std::string& data){return Key::isPressed(data, "{{{up}}}");}
};

class KeyRight : public Key {
public:
    KeyRight(){
        key = ">>";
        value = "{{{right}}}";
    }

    static bool isPressed(const std::string& data){return Key::isPressed(data, "{{{right}}}");}
};

class KeySpacer : public Key {
public:
    explicit KeySpacer(float sizeX){
        key = "";
        value = "";
        this->sizeX = sizeX;
    }

    KeySpacer(float sizeX, float sizeY){
        key = "";
        value = "";
        this->sizeX = sizeX;
        this->sizeY = sizeY;
    }
};

#endif //CARPI_KEY_H
