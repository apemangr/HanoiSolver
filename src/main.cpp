#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

const int windowWidth = 800;
const int windowHeight = 600;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Hanoi Solver",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          windowWidth,
                                          windowHeight,
                                          SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Error al crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Three Horizontal Rect's
    int rectHorWidth = 200;
    int rectHorHeight = 30;
    int spacingHor = 20;

    int rectVerWidth = 30;
    int rectVerHeight = 200;
    //int spacingVer = 500;



    SDL_Rect rectsHor[3];
    SDL_Rect rectsVer[3];

    for (int i = 0; i < 3; ++i) {
        rectsHor[i].w = rectHorWidth;
        rectsHor[i].h = rectHorHeight;
        rectsVer[i].w = rectVerWidth;
        rectsVer[i].h = rectVerHeight;

        rectsHor[i].x = (windowWidth - (3 * rectHorWidth + 2 * spacingHor)) / 2 + i * (rectHorWidth + spacingHor);
        rectsVer[i].x = rectsHor[i].x  + rectHorWidth / 2 - rectVerWidth / 2;
        rectsHor[i].y = (windowHeight - rectHorHeight) / 2 + 100;
        rectsVer[i].y = rectsHor[i].y / 2; 
    }

    // Three Vertical Rect's
       bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar los rectángulos
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < 3; ++i) {
            SDL_RenderFillRect(renderer, &rectsHor[i]);
        }
        for (int i = 0; i < 3; ++i) {
            SDL_RenderFillRect(renderer, &rectsVer[i]);
        }
        // Actualizar la pantalla
        SDL_RenderPresent(renderer);
    }

    // Limpiar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

