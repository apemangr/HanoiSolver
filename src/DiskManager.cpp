#include "../include/DiskManager.hpp"
#include "../include/main.hpp"
#include <iostream>
#include <array>
#include <cmath>

DiskManager::DiskManager(int disks_number) : towers_state(3){
    initialize_disks(DISKS_NUMBER);
    for (int i = 0; i < disks_number; ++i) {
        towers_state[0].push(i);  
    }
}

void DiskManager::render(){
    for (const auto& disk : disks) {
        disk.render();
    }
}

void DiskManager::generate_hanoi_moves(int n, int from, int to, int aux) {
    if (n == 1) {
        movements.push_back({from, to});
    } else {
        generate_hanoi_moves(n - 1, from, aux, to);
        movements.push_back({from, to});
        generate_hanoi_moves(n - 1, aux, to, from);
    }
}

void DiskManager::update(Towers &towers) {

    if (movements.empty()) {
        generate_hanoi_moves(DISKS_NUMBER, 0, 2, 1);
    }
   if (current_move < movements.size()) {
        int from = movements[current_move].first;
        int to = movements[current_move].second;
        
        if (!towers_state[from].empty()) {
            int disk_index = towers_state[from].top();  // Obtén el disco superior de la torre de origen
            Disk &disk = disks[disk_index];

            if (move_to_tower(disk, from, to, towers)) {
                towers_state[from].pop();          // Quita el disco de la torre de origen
                towers_state[to].push(disk_index); // Añade el disco a la torre de destino
                current_move++;  // Pasar al siguiente movimiento
            }
        }
    } 
}

bool DiskManager::move_to_tower(Disk &disk, int start_tower, int end_tower, Towers &tower) {

    static int state = 0;  // There are three states: 1. Up, 2. Left or Right, 3. Down
    int points[3][2] = {
        {disk.get_x(), SCREEN_HEIGHT / 5},
        {TOWER_X_POS[end_tower] - disk.get_width() / 2 + TOWER_PILAR_WIDTH / 2 , SCREEN_HEIGHT / 5}, 
        {TOWER_X_POS[end_tower] - disk.get_width() / 2 + TOWER_PILAR_WIDTH / 2 , DISKS_ORIGIN - (int)towers_state[end_tower].size() * TOWER_BASE_HEIGHT}
    };

    switch (state) {
        case 0:
            if(move_disk(disk, points[0][0], points[0][1]))
                state++;
            break;

        case 1:
            if(move_disk(disk, points[1][0], points[1][1]))
                state++;
            break;

        case 2:
            if(move_disk(disk, points[2][0], points[2][1])){
                state = 0;
                return true;
            }
            break;
           
    }

    return false;
}


bool DiskManager::move_disk(Disk &disk, int final_x, int final_y) {
    if (disk.get_x() == final_x && disk.get_y() == final_y) {
        return true;
    }

    int dx = std::abs(final_x - disk.get_x());
    int dy = std::abs(final_y - disk.get_y());
    int sx = disk.get_x() < final_x ? 1 : -1;
    int sy = disk.get_y() < final_y ? 1 : -1;

    // Aumenta la cantidad de píxeles que se mueve el disco en cada paso
    int step_size = 15; // Puedes ajustar este valor para aumentar o reducir la velocidad

    int err = dx - dy;
    int e2;

    e2 = 2 * err;
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

    return (disk.get_x() == final_x && disk.get_y() == final_y);
}

void DiskManager::initialize_disks(int disks_number){
    int base_width  = 150;
    int base_height = TOWER_BASE_HEIGHT;

    std::array<SDL_Color, 6> colors = {{
            {0x9a, 0x59, 0xb5, 0xFF},  // #9a59b5
            {0x34, 0x99, 0xdb, 0xFF},  // #3499db
            {0x2d, 0xcb, 0x71, 0xFF},  // #2dcb71
            {0xe9, 0x4c, 0x3d, 0xFF},  // #e94c3d
            {0xff, 0x8c, 0x00, 0xFF},  // #ff8c00
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
