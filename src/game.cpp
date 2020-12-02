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
        startTime = SDL_GetPerformanceCounter();
        draw();
    }
}

void Game::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Initialize renderer for window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    font = nullptr;

    isRunning = true;

    now = SDL_GetPerformanceCounter();

    //Initialize PNG loading
    IMG_Init(IMG_INIT_PNG);

    //Initialize ttf loading
    TTF_Init();
}

void Game::loadContent() {
    pacmanTexture.loadFromFile("Content/pacman.png", renderer);
    font = TTF_OpenFont("Content/PressStart2P.ttf", 10);
    
    //Render text to texture of text
    textColor = {232, 178, 178};
    textTexture.loadFromRenderedText("Press Start", textColor, font, renderer);   
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
    //Update logic
    now = SDL_GetPerformanceCounter();
    deltaTime = (double)((now - startTime)*1000 / (double)SDL_GetPerformanceFrequency());
    timeText.str("");
    timeText << deltaTime << " ms";
    //Render text
    textTexture.loadFromRenderedText(timeText.str().c_str(), textColor, font, renderer);
}

void Game::draw() {
    //Clear screen
    SDL_RenderClear(renderer);
    
    //Render texture to screen
    pacmanTexture.render(renderer, 0, 0);
    textTexture.render(renderer, (SCREEN_WIDTH - textTexture.getWidth())/2, (SCREEN_HEIGHT - textTexture.getHeight())/2);

    //Update screen
    SDL_RenderPresent(renderer);
}

void Game::exit() {
    isRunning = false;
}

void Game::cleanAndQuit() {
    //Free loaded images
    pacmanTexture.free();
    textTexture.free();

    //Free font
    TTF_CloseFont(font);
    font = nullptr;

    //Destroy Window
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}