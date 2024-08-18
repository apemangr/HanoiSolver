#include "../include/DiskManager.hpp"
#include "../include/Screen.hpp"
#include "../include/Towers.hpp"
#include "../include/Button.hpp"
#include "../include/main.hpp"

#include <iostream>

SDL_Renderer *Screen::renderer = nullptr;
Towers *towers;

// font stuff
TTF_Font *font = nullptr;
SDL_Texture *title_texture = nullptr;
SDL_Surface *title_surface = nullptr;
SDL_Rect dstRect = {100, 100, 200, 50};

// Button stuff
Button *myButton;

//

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

        // Inicializar SDL_ttf
        if (TTF_Init() == 0) {
            std::cout << "[\033[32m OK \033[0m] Fonts initialized correctly!" << std::endl;

            // Cargar la fuente
            //font = TTF_OpenFont("../assets/SEVESBRG.TTF", 48);
            font = TTF_OpenFont("../assets/Sporta.ttf", 58);
            if (font) {
                std::cout << "[\033[32m OK \033[0m] Font Sporta loaded!" << std::endl;

                // Renderizar el texto a una superficie
                SDL_Color color = {255, 255, 255};
                title_surface = TTF_RenderText_Blended(font, "Hanoi Solver", color);
                if (title_surface) {
                    // Crear la textura desde la superficie
                    title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);
                    if (!title_texture) {
                        std::cerr << "[\033[31m ERROR \033[0m] Failed to create texture: " << SDL_GetError() << std::endl;
                    }else{
                        dstRect.w = title_surface->w;
                        dstRect.h = title_surface->h;
                        dstRect.x = SCREEN_WIDTH / 2  - title_surface->w / 2;
                        dstRect.y = SCREEN_HEIGHT/ 5  - title_surface->h * 2 ;
                    }

                } else {
                    std::cerr << "[\033[31m ERROR \033[0m] Failed to create surface: " << TTF_GetError() << std::endl;
                }
            } else {
                std::cerr << "[\033[31m ERROR \033[0m] Failed to load font: " << TTF_GetError() << std::endl;
            }
        } else {
            std::cerr << "[\033[31m ERROR \033[0m] Failed to initialize TTF: " << TTF_GetError() << std::endl;
        }

        myButton = new Button(200, 200, "Hola", {255, 255, 255, 255}, {0, 0, 0, 0}, font);


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
    
    // disk part
    // towers->render();
    // disks->render();

    // title
     SDL_RenderCopy(renderer, title_texture, nullptr, &dstRect); 




//    std::cout << "Rendering button" << std::endl;

    myButton->render();

//    std::cout << "Done button" << std::endl;




    SDL_RenderPresent(renderer);
}

void Screen::clean(){
    SDL_FreeSurface(title_surface);
}
