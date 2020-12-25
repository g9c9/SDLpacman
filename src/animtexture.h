#ifndef ANIMTEXTURE_H
#define ANIMTEXTURE_H
#include "texture.h"

class AnimTexture : public Texture {
public:
    AnimTexture();
    ~AnimTexture();

    //Loads image at specified path and initializes animated texture
    bool loadFromFile(string path, int frames, double SpF, int frameWidth, int frameHeight, SDL_Renderer* renderer);

    void update(double &);

    virtual void render(SDL_Renderer* renderer, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    int index;
    int frames;
    int frameWidth;
    int frameHeight;
    double SpF;
};

#endif