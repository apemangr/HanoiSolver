#ifndef DISK_MANAGER_HPP
#define DISK_MANAGER_HPP

#include "Towers.hpp"
#include "Disk.hpp"
#include <stack>
#include <vector>

class DiskManager{

public:
    DiskManager(int disks_number);
    
    void render();
    void update(Towers &tower);
    void initialize_disks(int disks_number);
    bool move_disk(Disk &disk, int final_x, int final_y);
    bool move_to_tower(Disk &disk, int start_tower, int end_tower, Towers &tower);

private:
    std::vector<std::pair<int, int>> movements;
    int current_move = 0;
    std::vector<Disk> disks;
    void generate_hanoi_moves(int n, int from, int to, int aux);
    std::vector<std::stack<int>> towers_state;

};

#endif /* DISK_MANAGER_HPP */
