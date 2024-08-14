#include "../include/DiskManager.hpp"
#include "../include/Towers.hpp"
#include "../include/main.hpp"
#include <iostream>
#include <array>
#include <cmath>

DiskManager::DiskManager(int disks_number)
{
    initialize_disks(DISKS_NUMBER);
}

void DiskManager::render()
{
    for (const auto& disk : disks) {
        disk.render();
    }
}

void DiskManager::update(){
//     for (const auto& disk : disks) {
//         disk.update();
//     }
    // move_disk(disks[0], disks[0].get_x(), 30);
    move_to_tower(disks[2], 0, 2);
}

// bool DiskManager::move_to_tower(Disk &disk, int start_tower, int end_tower){
//     // const bool move_one = false;
//     // const bool move_two = false;
//     // const bool move_thr = false;
//
//     // move_one
//     if (disk.get_y() != SCREEN_WIDTH / 5 && TOWER_X_POS[start_tower] - disk.get_width() / 2 == disk.get_x()){
//         if(move_disk(disk, TOWER_X_POS[start_tower] - disk.get_width() / 2, SCREEN_WIDTH / 5 )){
//             std::cout << "Punto A logrado" << std::endl;
//         }
//     }
//     // if (move_one && !move_two) {
//     //     if(move_disk(disk, TOWER_X_POS[end_tower] - disk.get_width() / 2, SCREEN_WIDTH / 5)){
//     //         move_two = true;
//     //     }
//     // }
//
//
//     return true; 
// }

// bool DiskManager::move_to_tower(Disk &disk, int start_tower, int end_tower){
//
//     std::cout << TOWER_X_POS[end_tower]   - disk.get_width() / 2  + TOWER_PILAR_WIDTH / 2 << std::endl;
//     std::cout << SCREEN_HEIGHT / 5 << std::endl;
//     if(!move_disk(disk, TOWER_X_POS[start_tower] - disk.get_width() / 2 + TOWER_PILAR_WIDTH / 2, SCREEN_HEIGHT / 5)){
//         std::cout << "Punto 1 -> X: " << disk.get_x() << " Y: " << disk.get_y() << std::endl;
//         return false;
//     }
//
//     if(!move_disk(disk, TOWER_X_POS[end_tower]   - disk.get_width() / 2  + TOWER_PILAR_WIDTH / 2, SCREEN_HEIGHT / 5)){
//         std::cout << "Punto 2 -> X: " << disk.get_x() << " Y: " << disk.get_y() << std::endl;
//         // std::cout << "Tower final: " << TOWER_X_POS[end_tower] << std::endl;
//         return false;
//     }
//
//     std::cout << "Punto 3 -> X: " << disk.get_x() << "Y: " << disk.get_y() << std::endl;
//     return move_disk(disk, TOWER_X_POS[end_tower] - disk.get_width() / 2  , 500);
//
// }



bool DiskManager::move_to_tower(Disk &disk, int start_tower, int end_tower) {
    static int current_point = 0;
    static int points[3][2] = {
        {disk.get_x(), SCREEN_HEIGHT / 5},
        {TOWER_X_POS[end_tower] - disk.get_width() / 2, SCREEN_HEIGHT / 5}, 
        {541, 300}
    };

    static bool completed = false;

    if(completed){
        return true;
    }
    
    bool reached_point = move_disk(disk, points[current_point][0], points[current_point][1]);
    
    if (reached_point) {
        current_point++;
        if (current_point >= 3) {
            current_point = 0;  // Resetear para el próximo uso
            completed = true;
            return true;  // Hemos llegado al último punto
        }
    }
    
    return false;  // Aún no hemos completado todos los puntos
}

bool DiskManager::move_disk(Disk &disk, int final_x, int final_y) {
    if(disk.get_x() == final_x && disk.get_y() == final_y) {
        return true;
    }
    
    int dx = std::abs(final_x - disk.get_x());
    int dy = std::abs(final_y - disk.get_y());
    int sx = disk.get_x() < final_x ? 1 : -1;
    int sy = disk.get_y() < final_y ? 1 : -1;

    // Aumenta la cantidad de píxeles que se mueve el disco en cada paso
    int step_size = 3; // Puedes ajustar este valor para aumentar o reducir la velocidad

    static int err = dx - dy;
    static bool isFirstCall = true;

    if (isFirstCall) {
        err = dx - dy;
        isFirstCall = false;
    }

    int e2 = 2 * err;
    if (e2 > -dy) {
        err -= dy;
        disk.set_position(disk.get_x() + sx * step_size, disk.get_y());
    }
    if (e2 < dx) {
        err += dx;
        disk.set_position(disk.get_x(), disk.get_y() + sy * step_size);
    }


    // Si superamos la posición final, corregimos para no pasarnos
    if (std::abs(final_x - disk.get_x()) < step_size) {
        disk.set_position(final_x, disk.get_y());
    }
    if (std::abs(final_y - disk.get_y()) < step_size) {
        disk.set_position(disk.get_x(), final_y);
    }

    if (disk.get_x() == final_x && disk.get_y() == final_y) {
        isFirstCall = true;  // Reseteamos para el próximo uso
        return true;  // Hemos llegado al destino
    }

    return false;
}


void DiskManager::initialize_disks(int disks_number){
    int base_width  = 150;
    int base_height = 30;
    std::array<SDL_Color, 5> colors = {{
            {0x9a, 0x59, 0xb5, 0xFF},  // #9a59b5
            {0x34, 0x99, 0xdb, 0xFF},  // #3499db
            {0x2d, 0xcb, 0x71, 0xFF},  // #2dcb71
            {0xe9, 0x4c, 0x3d, 0xFF},  // #e94c3d
            {0xf0, 0xc4, 0x11, 0xFF}   // #f0c411
    }};

    for (int i = 0; i < disks_number; i++) 
    {
        int width = base_width - i * 16;
        disks.emplace_back(width, base_height, colors[i]);
        disks[i].set_position(
                ( SCREEN_WIDTH  / 4 ) - disks[i].get_width() / 2,
                ( SCREEN_HEIGHT / 3 ) * 2 - (i + 1) * base_height - base_height / 2);

        std::cout << "The position of the disk " << i << " is: " << disks[i].get_height() << std::endl;
    }
}
