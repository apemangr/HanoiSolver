#ifndef DISK_MANAGER_HPP
#define DISK_MANAGER_HPP

#include "Disk.hpp"
#include <vector>

class DiskManager{

public:
    DiskManager(int disks_number);
    
    void render();
    void update();
    void initialize_disks(int disks_number);
    bool move_disk(Disk &disk, int final_x, int final_y);
    bool move_to_tower(Disk &disk, int start_tower, int end_tower);

private:
    std::vector<Disk> disks;
};



#endif /* DISK_MANAGER_HPP */
