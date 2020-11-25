#include "game.h"

Game::Game() {
    initialize();
    loadContent();
}

Game::~Game() {
    cleanAndQuit();
}

void Game::Run() {
    while (isRunning) {
        update();
        draw();
    }
}

void Game::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    //Initialize renderer for window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    pacmanTexture = nullptr;

    isRunning = true;

    //Initialize PNG loading
    IMG_Init(IMG_INIT_PNG);
}

void Game::loadContent() {
    pacmanTexture = LoadTexture("Content/pacman.png");
}

void Game::update() {
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit();
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                exit();
            }
        }
    }
}

void Game::draw() {
    //Clear screen
    SDL_RenderClear(renderer);
    
    //Render texture to screen
    SDL_RenderCopy(renderer, pacmanTexture, NULL, NULL);

    //Update screen
    SDL_RenderPresent(renderer);
}

void Game::exit() {
    isRunning = false;
}

void Game::cleanAndQuit() {
    //Free loaded images
    SDL_DestroyTexture(pacmanTexture);
    pacmanTexture = nullptr;

    //Destroy Window
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Game::LoadTexture(string path) {
    SDL_Texture* newTexture = nullptr;
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr) {
        exit();
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr) {
            exit();
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}