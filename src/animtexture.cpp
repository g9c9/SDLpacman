#include "animtexture.h"

AnimTexture::AnimTexture() {
    index = 0;
    frames = 0;
    frameWidth = 0;
    frameHeight = 0;
    SpF = 0;
}

AnimTexture::~AnimTexture() {
}

bool AnimTexture::loadFromFile(string path, int frames, double SpF, int frameWidth, int frameHeight, SDL_Renderer* renderer) {
    //Get rid of preexisting texture if there is any
    free();

    //The final texture
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        return false;
    }
    else {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == nullptr) {
            return false;
        }
        width = loadedSurface->w;
        height = loadedSurface->h;
        this->frames = frames;
        this->SpF = SpF;
        this->frameWidth = frameWidth;
        this->frameHeight = frameHeight;
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}

//Pass in timer
void AnimTexture::update(double &deltaTime) {
    if (deltaTime >= SpF) {
        deltaTime = 0;
        if (index == frames - 1) {
            index = 0;
        }
        else {
            index++;
        }
    }
}

void AnimTexture::render(SDL_Renderer* renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect clip = {index * frameWidth, 0, frameWidth, frameHeight};
    SDL_Rect renderQuad = {x, y, frameWidth, frameHeight};
    SDL_RenderCopyEx(renderer, texture, &clip, &renderQuad, angle, center, flip);
}