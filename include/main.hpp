#ifndef MAIN_HPP
#define MAIN_HPP

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 640;
const int DISKS_NUMBER  = 5;
const int TOWER_BASE_HEIGHT  = 30;
const int TOWER_BASE_WIDTH   = 180;
const int TOWER_PILAR_HEIGHT = 200;
const int TOWER_PILAR_WIDTH  = 30;
const int DISKS_ORIGIN = SCREEN_HEIGHT / 3 * 2 - TOWER_BASE_HEIGHT / 2 - TOWER_BASE_HEIGHT;
const int TOWER_X_POS[3] = {
    ( SCREEN_WIDTH / 4 ) * ( 1 ) - TOWER_PILAR_WIDTH / 2,
    ( SCREEN_WIDTH / 4 ) * ( 2 ) - TOWER_PILAR_WIDTH / 2,
    ( SCREEN_WIDTH / 4 ) * ( 3 ) - TOWER_PILAR_WIDTH / 2
};


#endif
