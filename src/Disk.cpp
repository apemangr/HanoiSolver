#include "../include/Disk.hpp"
#include "../include/Screen.hpp"

Disk::Disk(int width, int height, SDL_Color color)
    : rect{0, 0, width, height}, color(color) {}

void Disk::render() const{
    SDL_SetRenderDrawColor(Screen::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Screen::renderer, &rect);
}

void Disk::set_position(int x, int y){
    Disk::rect.x = x;
    Disk::rect.y = y;
}

int Disk::get_width(){
    return Disk::rect.w;
}

int Disk::get_height(){
    return Disk::rect.h;
}
