#ifndef WUMPUS_FUNCTIONS_H
#define WUMPUS_FUNCTIONS_H

#include <array>

using namespace std;

array<int, 2> random_position(array<int, 2> lCDim);

void check_bounds(array<int, 2> pos, array<int, 2> cDim, bool *ptr);

bool check_same_location(array<int, 2> pos1, array<int, 2> pos2);

bool check_if_neighboring(array<int, 2> hpos, array<int, 2> objpos);

void get_size(array<int, 2> *cDimptr);

void gen_world(array<int, 2> *cDimptr, array<int, 2> *hposptr, array<int, 2> *p1posptr, array<int, 2> *p2posptr, array<int, 2> *b1posptr, array<int, 2> *b2posptr, array<int, 2> *wposptr);

char player_decision();

void player_move(array<int, 2> *hposptr, array<int, 2> *cDimptr);

bool player_shoot(array<int, 2> *hposptr, array<int, 2> *wposptr, array<int, 2> *cDimptr);

void move_object(array<int, 2> *objptr, array<int, 2> *cDimptr);

void check_nearby(array<int, 2> *hposptr, array<int, 2> *p1posptr, array<int, 2> *p2posptr, array<int, 2> *wposptr);

void check_player_tile(bool *hAliveptr, bool *wAliveptr, array<int, 2> cDimptr, array<int, 2> *hposptr, array<int, 2> *p1posptr, array<int, 2> *p2posptr, array<int, 2> *b1posptr, array<int, 2> *b2posptr, array<int, 2> *wposptr);

void play_game();

#endif