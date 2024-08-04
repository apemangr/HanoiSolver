#define SDL_MAIN_HANDLED

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <iostream>

const int windowWidth = 800;
const int windowHeight = 600;
int numberOfDiscs = 9;

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
} ColoredRect;

// Generate a function that moves a discs from point A to point B
void moveDisc(ColoredRect *coloredRect, int endX) {
    int first = 0;
    if(first==0 && coloredRect->rect.y != 10) {
        coloredRect->rect.y -= 1;
    }
    if(coloredRect->rect.y == 10)
        first = 1;

    if (coloredRect->rect.x != endX && first == 1) {
        coloredRect->rect.x += 1;
    }

     
    SDL_Delay(20);
}

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

    enum {
        FirstPil,
        SecondPil,
        ThirdPil,
    };

    SDL_Rect rectsHor[3];
    SDL_Rect rectsVer[3];
    ColoredRect discs[numberOfDiscs];

    int firstPilarX = (windowWidth - (3 * rectHorWidth + 2 * spacingHor)) / 2 + 0 * (rectHorWidth + spacingHor);
    int secondPilX  = (windowWidth - (3 * rectHorWidth + 2 * spacingHor)) / 2 + 1 * (rectHorWidth + spacingHor);
    int thirdPilX   = (windowWidth - (3 * rectHorWidth + 2 * spacingHor)) / 2 + 2 * (rectHorWidth + spacingHor);
    int rectsX[3] = {firstPilarX, secondPilX, thirdPilX};

    for (int i = 0; i < 3; ++i) {
        rectsHor[i].w = rectHorWidth;
        rectsHor[i].h = rectHorHeight;
        rectsVer[i].w = rectVerWidth;
        rectsVer[i].h = rectVerHeight;

        rectsHor[i].x = rectsX[i];
        rectsVer[i].x = rectsHor[i].x  + rectHorWidth / 2 - rectVerWidth / 2;
        rectsHor[i].y = (windowHeight - rectHorHeight) / 2 + 100;
        rectsVer[i].y = rectsHor[i].y / 2; 
    }

    for (int i = 0; i < numberOfDiscs; ++i) {
        discs[i].rect.w = rectHorWidth - (i * 10) - 20;
        discs[i].rect.h = rectHorHeight - 10;
        discs[i].rect.x = rectsVer[FirstPil].x - discs[i].rect.w / 2 + rectVerWidth / 2;
        discs[i].rect.y = rectsHor[FirstPil].y - i * 20 - 20;
        discs[i].color.r = rand() % 256;
        discs[i].color.g = rand() % 256;
        discs[i].color.b = rand() % 256;
        discs[i].color.a = 255;  
    }

    bool running = true;

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        /////// MLStart
        // 
        //

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render base pilars
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < 3; ++i) {
            SDL_RenderFillRect(renderer, &rectsHor[i]);
        }

        // Render Pilars
        for (int i = 0; i < 3; ++i) {
            SDL_RenderFillRect(renderer, &rectsVer[i]);
        }

        // Render Discs
        for (int i = 0; i < numberOfDiscs; ++i) {
            SDL_SetRenderDrawColor(renderer, discs[i].color.r, discs[i].color.g, discs[i].color.b, discs[i].color.a);
            SDL_RenderFillRect(renderer, &discs[i].rect);
        }
        moveDisc(&discs[0], 500);
        SDL_RenderPresent(renderer);

        //
        //
        /////// MLEnd
    }


    // Limpiar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

