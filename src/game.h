#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using namespace std;

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;

    SDL_Event event;

    //Texture of pacman
    SDL_Texture* pacmanTexture;

    void initialize();
    void loadContent();
    void update();
    void draw();
    void exit();
    void cleanAndQuit();

    SDL_Texture* LoadTexture(string);
};

#endif