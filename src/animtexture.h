#ifndef ANIMTEXTURE_H
#define ANIMTEXTURE_H
#include "texture.h"

class AnimTexture : public Texture {
public:
    AnimTexture();
    ~AnimTexture();

    //Loads image at specified path and initializes animated texture
    bool loadFromFile(string, int, double, int, int, SDL_Renderer*);

    void update(double &);

    virtual void render(SDL_Renderer*, const int, const int) const;

private:
    int index;
    int frames;
    int frameWidth;
    int frameHeight;
    double SpF;
};

#endif