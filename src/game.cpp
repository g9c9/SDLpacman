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
        //Deltatime logic
        deltaTime = (double)((SDL_GetPerformanceCounter() - startTime)*1000 / (double)SDL_GetPerformanceFrequency());

        //Keystate logic
        newKeyState = SDL_GetKeyboardState(NULL);

        update();

        oldKeyState = newKeyState;

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

    newKeyState = SDL_GetKeyboardState(NULL);

    //Initialize pacman state
    pstate = F;

    //Initialize PNG loading
    IMG_Init(IMG_INIT_PNG);

    //Initialize ttf loading
    TTF_Init();
}

void Game::loadContent() {
    pacmanTexture.loadFromFile("Content/pacman.png", renderer);
    animPacmanTexture.loadFromFile("Content/eating.png", 5, PACMAN_EATING_SPF, 16, 16, renderer);
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

        // case SDL_KEYDOWN:
        //     if (event.key.keysym.sym == SDLK_ESCAPE)
        //     {
        //         exit();
        //     }
        }
    }

    //Keyboard input logic
    if(keyJustPressed(SDL_SCANCODE_ESCAPE)) {
        exit();
    }

    //Update logic
    //Keyboard logic for pacman
    if(keyJustPressed(SDL_SCANCODE_D) || keyHolding(SDL_SCANCODE_D)) {
        pstate = MR;
    }
    else if(keyJustPressed(SDL_SCANCODE_A) || keyHolding(SDL_SCANCODE_A)) {
        pstate = ML;
    }
    else if(keyJustPressed(SDL_SCANCODE_W) || keyHolding(SDL_SCANCODE_W)) {
        pstate = MU;
    }
    else if(keyJustPressed(SDL_SCANCODE_S) || keyHolding(SDL_SCANCODE_S)) {
        pstate = MD;
    }
    else {
        pstate = F;
    }

    if(pstate == F) {
        timer = 0;
    }
    else {
        timer += deltaTime;
        animPacmanTexture.update(timer);
    }
}

void Game::draw() {
    //Clear screen
    SDL_RenderClear(renderer);
    
    //Render texture to screen
    //pacmanTexture.render(renderer, (SCREEN_WIDTH - pacmanTexture.getWidth())/2, (SCREEN_HEIGHT - pacmanTexture.getHeight())/2);
    //animPacmanTexture.render(renderer, (SCREEN_WIDTH - pacmanTexture.getWidth())/2, (SCREEN_HEIGHT - pacmanTexture.getHeight())/2);
    //textTexture.render(renderer, (SCREEN_WIDTH - textTexture.getWidth())/2, (SCREEN_HEIGHT - textTexture.getHeight())/2);
    if(pstate == F) {
        pacmanTexture.render(renderer, (SCREEN_WIDTH - pacmanTexture.getWidth())/2, (SCREEN_HEIGHT - pacmanTexture.getHeight())/2, 0, NULL, SDL_FLIP_NONE);
    }
    else if(pstate == MR) {
        animPacmanTexture.render(renderer, (SCREEN_WIDTH - pacmanTexture.getWidth())/2, (SCREEN_HEIGHT - pacmanTexture.getHeight())/2, 0, NULL, SDL_FLIP_NONE);
    }
    else if(pstate == ML) {
        animPacmanTexture.render(renderer, (SCREEN_WIDTH - pacmanTexture.getWidth())/2, (SCREEN_HEIGHT - pacmanTexture.getHeight())/2, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else if(pstate == MU) {
        animPacmanTexture.render(renderer, (SCREEN_WIDTH - pacmanTexture.getWidth())/2, (SCREEN_HEIGHT - pacmanTexture.getHeight())/2, -90, NULL, SDL_FLIP_NONE);
    }
    else if(pstate == MD) {
        animPacmanTexture.render(renderer, (SCREEN_WIDTH - pacmanTexture.getWidth())/2, (SCREEN_HEIGHT - pacmanTexture.getHeight())/2, -90, NULL, SDL_FLIP_HORIZONTAL);
    }
    

    //Update screen
    SDL_RenderPresent(renderer);
}

void Game::exit() {
    isRunning = false;
}

void Game::cleanAndQuit() {
    //Free loaded images
    pacmanTexture.free();
    animPacmanTexture.free();
    textTexture.free();

    //Free font
    TTF_CloseFont(font);
    font = nullptr;

    //Free keyboard state pointers
    newKeyState = nullptr;

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

bool Game::keyJustPressed(SDL_Scancode keyCode) {
    return !oldKeyState[keyCode] && newKeyState[keyCode];
}

bool Game::keyHolding(SDL_Scancode keyCode) {
    return oldKeyState[keyCode] && newKeyState[keyCode];
}

bool Game::keyLetGo(SDL_Scancode keyCode) {
    return oldKeyState[keyCode] && !newKeyState[keyCode];
}