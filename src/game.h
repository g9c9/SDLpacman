#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "texture.h"
#include "animtexture.h"
#include <sstream>
#include "keystate.h"
using namespace std;

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    //In terms of milliseconds
    const double PACMAN_EATING_SPF = 50;

    enum PState {F, MU, MD, ML, MR};
    PState pstate;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;

    SDL_Event event;

    //Texture of pacman
    Texture pacmanTexture;

    //Animated Texture of pacman
    AnimTexture animPacmanTexture;

    //Font
    TTF_Font* font;

    //Texture for rendered text
    Texture textTexture;

    //Color for text
    SDL_Color textColor;

    //Current start time
    Uint64 startTime = 0;

    //deltaTime
    double deltaTime = 0;

    //Timer for pacman
    double timer;

    //In memory text stream
    stringstream timeText;

    //Key states
    const Uint8* newKeyState;
    KeyState oldKeyState;

    void initialize();
    void loadContent();
    void update();
    void draw();
    void exit();
    void cleanAndQuit();
    bool keyJustPressed(SDL_Scancode);
    bool keyHolding(SDL_Scancode);
    bool keyLetGo(SDL_Scancode);
};

#endif