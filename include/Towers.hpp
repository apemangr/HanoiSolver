#ifndef TOWERS_HPP
#define TOWERS_HPP
#include <SDL2/SDL_rect.h>

class Towers{

public:
    Towers();
    ~Towers();

    void render();

private:
    SDL_Rect tower_base[3];
    SDL_Rect tower_pilar[3];
};

#endif /* TOWERS_HPP */
