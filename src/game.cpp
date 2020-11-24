#include "game.h"

Game::Game() {
    Initialize();
    LoadContent();
}

Game::~Game() {
    CleanAndQuit();
}

void Game::Run() {
    while (isRunning) {
        Update();
        Draw();
    }
}

void Game::Initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    isRunning = true;

    //Initialize PNG loading
    IMG_Init(IMG_INIT_PNG);
}

void Game::LoadContent() {

}

void Game::Update() {
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Exit();
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                Exit();
            }
        }
    }
}

void Game::Draw() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);
}

void Game::Exit() {
    isRunning = false;
}

void Game::CleanAndQuit() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}