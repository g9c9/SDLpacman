//Wrapper class for SDL_Texture
#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class Texture {
public:
    //Initializes variables
    Texture();
    ~Texture();

    //Loads image at specified path
    bool loadFromFile(string, SDL_Renderer*);

    //Creates image from font string
    bool loadFromRenderedText(string, SDL_Color, TTF_Font*, SDL_Renderer*);

    //Renders texture at given point
    virtual void render(SDL_Renderer*, const int, const int) const;

    //Deallocates texture
    void free();

    //Gets image dimensions
    int getWidth();
    int getHeight();
protected:
    //The actual hardware texture
    SDL_Texture* texture;

    //Image dimensions
    int width;
    int height;

    
};

#endif