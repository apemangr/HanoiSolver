#ifndef DISK_HPP
#define DISK_HPP

#include <SDL2/SDL.h>

class Disk{

public:
    Disk(int width, int height, SDL_Color color);

    void set_position(int x, int y);
    void render() const;
    int  get_width();
    int  get_height();
    int get_x(){ return rect.x; }
    int get_y(){ return rect.y; }
    void set_animating(bool new_state){ is_animating = new_state; }
    bool get_animating(){ return is_animating; }
    
private:
    SDL_Color color;
    SDL_Rect rect;
    bool is_animating;
};

#endif /* DISk_HPP */
