#include "texture.h"

Texture::Texture(string path, SDL_Renderer* renderer) {
    texture = nullptr;
    width = 0;
    height = 0;
    loadFromFile(path, renderer);
}

Texture::~Texture() {
    //Deallocate
    free();
}

bool Texture::loadFromFile(string path, SDL_Renderer* renderer) {
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
        SDL_FreeSurface(loadedSurface);
        return true;
    }
}

void Texture::free() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void Texture::render(SDL_Renderer* renderer, int x, int y) const {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}