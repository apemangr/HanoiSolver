#include "../include/DiskManager.hpp"
#include "../include/Screen.hpp"
#include "../include/Towers.hpp"
#include "../include/main.hpp"

#include <iostream>

SDL_Renderer *Screen::renderer = nullptr;
Towers *towers;
TTF_Font *font = TTF_OpenFont("assets/Sporta.ttf", 24);
DiskManager *disks;

Screen::Screen(){}

Screen::~Screen(){}

void Screen::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "[\033[32m OK \033[0m] Initializing SDL" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            std::cout << "[\033[32m OK \033[0m] Initializing the window" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, flags);
        if(renderer){
            std::cout << "[\033[32m OK \033[0m] Initializing the renderer" << std::endl;
        }

        is_running = true;
        towers = new Towers();
        disks = new DiskManager(DISKS_NUMBER);

        if(TTF_Init() == 0){
            std::cout << "[\033[32m OK \033[0m] Fonts initialized correctly!" << std::endl;
        }
        if(font){
            std::cout << "[\033[32m OK \033[0m] Font Sporta loaded!" << std::endl;
        }


    } else {
        is_running = false;
    }
}

void Screen::handle_events(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}

void Screen::update(){
    disks->update(*towers);
}

void Screen::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    towers->render();
    disks->render();


    SDL_RenderPresent(renderer);
}

void Screen::clean(){

}
