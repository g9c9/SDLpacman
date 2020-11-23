#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

    void Initialize();
    void LoadContent();
    void Update();
    void Draw();
    void Exit();
    void CleanAndQuit();
};

#endif