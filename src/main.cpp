#define main SDL_main

#include "../include/Screen.hpp"
#include "../include/main.hpp"

Screen *screen = nullptr;

int main(int argc, char *argv[]){

    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    int frame_time;
    Uint64 frame_start;

    screen = new Screen();
    screen->init(
            "HanoiSolver",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, 
            SCREEN_HEIGHT, 
            false
            );

    while(screen->running()){

        frame_start = SDL_GetTicks();

        screen->handle_events();
        screen->render();
        screen->update();

        frame_time = SDL_GetTicks64() - frame_start;

        if(frame_delay > frame_time){
            SDL_Delay(frame_delay - frame_time);
        }

    }
    screen->clean();
    return 0;    
}
