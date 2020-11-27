#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "texture.h"
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

    void initialize();
    void loadContent();
    void update();
    void draw();
    void exit();
    void cleanAndQuit();
};

#endif