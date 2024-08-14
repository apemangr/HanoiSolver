#include "../include/Towers.hpp"
#include "../include/Screen.hpp"
#include "../include/main.hpp"

Towers::Towers() {
    for (int i = 0; i < 3; i++) {
        tower_pilar[i].x = TOWER_X_POS[i];
        tower_pilar[i].y = SCREEN_HEIGHT / 3;
        tower_pilar[i].h = TOWER_PILAR_HEIGHT;
        tower_pilar[i].w = TOWER_PILAR_WIDTH;
        // std::cout << "Pilar " << i << " valor en X: " << tower_pilar[i].x << std::endl;
        tower_base[i].x  = tower_pilar[i].x - TOWER_BASE_WIDTH / 2 + TOWER_PILAR_WIDTH / 2;
        tower_base[i].y  = tower_pilar[i].y * 2 - TOWER_BASE_HEIGHT / 2;
        tower_base[i].h  = TOWER_BASE_HEIGHT;
        tower_base[i].w  = TOWER_BASE_WIDTH;
    }
    tower_offset[0] = DISKS_NUMBER * TOWER_BASE_HEIGHT;
    for(int i = 1; i < DISKS_NUMBER; i++){
        tower_offset[i] = 0;
    }
}

int Towers::get_tower_offset(Towers *tower, int tower_number){
    return tower->tower_offset[tower_number];
}

void Towers::render() {

    SDL_SetRenderDrawColor(Screen::renderer, 255, 255, 255, 255);

    // Renderizar las bases de las torres
    for (int i = 0; i < 3; ++i) {
        SDL_RenderFillRect(Screen::renderer, &tower_base[i]);
    }

    // Renderizar los pilares de las torres
    for (int i = 0; i < 3; ++i) {
        SDL_RenderFillRect(Screen::renderer, &tower_pilar[i]);
    }
}
