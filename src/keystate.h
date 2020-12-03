#ifndef KEYSTATE_H
#define KEYSTATE_H
#include <SDL2/SDL.h>
using namespace std;

class KeyState {
public:
    KeyState();
    ~KeyState();
    Uint8 operator[] (SDL_Scancode) const;
    void operator= (const Uint8*);
private:
    Uint8* arrayPtr;
    const int SIZE = 284;
};

#endif