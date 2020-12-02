#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "texture.h"
#include <sstream>
using namespace std;

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;

    SDL_Event event;

    //Texture of pacman
    Texture pacmanTexture;

    //Font
    TTF_Font* font;

    //Texture for rendered text
    Texture textTexture;

    //Color for text
    SDL_Color textColor;

    //Current start time
    Uint64 startTime = 0;

    //Current time
    Uint64 now;

    //deltaTime
    double deltaTime = 0;

    //In memory text stream
    stringstream timeText;

    void initialize();
    void loadContent();
    void update();
    void draw();
    void exit();
    void cleanAndQuit();
};

#endif