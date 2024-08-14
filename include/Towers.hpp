#ifndef TOWERS_HPP
#define TOWERS_HPP
#include <SDL2/SDL_rect.h>
#include "main.hpp"

class Towers{

public:
    Towers();
    ~Towers();

    void render();
    int  get_tower_offset(Towers *tower, int tower_number);

private:
    SDL_Rect tower_base[3];
    SDL_Rect tower_pilar[3];
    int tower_offset[DISKS_NUMBER];
};

#endif /* TOWERS_HPP */
