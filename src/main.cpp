#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "game.h"
using namespace std;

int main(int argv, char* args[])
{
    Game* game = new Game();
    game->Run();
    return 0;
}