//Wrapper class for SDL_Texture
#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using namespace std;

class Texture {
public:
    //Initializes variables
    Texture();
    ~Texture();

    //Loads image at specified path
    bool loadFromFile(string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(const int, const int) const;

    //Gets image dimensions
    int getWidth();
    int getHeight();
private:
    //The actual hardware texture
    SDL_Texture* texture;

    //Image dimensions
    int Width;
    int Height;
};

#endif