#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Screen{

public:
    Screen();
    ~Screen();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handle_events();
    void update();
    void render();
    void clean();
    bool running(){ return is_running;}
    static SDL_Renderer *renderer;

private:
    bool is_running;
    SDL_Window *window;
};

#endif /* SCREEN_HPP */
