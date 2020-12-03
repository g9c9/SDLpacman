#include "keystate.h"

//Default Constructor
KeyState::KeyState() {
    arrayPtr = new Uint8[SIZE];
    for(int i = 0; i < SIZE; i++) {
        arrayPtr[i] = 0;
    }
}

//Default Destructor
KeyState::~KeyState() {
    delete [] arrayPtr;
    arrayPtr = nullptr;
}

Uint8 KeyState::operator[](SDL_Scancode keyCode) const {
    return arrayPtr[keyCode];
}

void KeyState::operator=(const Uint8* keyState) {
    for(int i = 0; i < SIZE; i++) {
        arrayPtr[i] = keyState[i];
    }
}