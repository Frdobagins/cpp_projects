#include "wumpus_functions.h"

#include <array>
#include <iostream>
#include <random>
using namespace std;

array<int, 2> random_position(array<int, 2> lCDim) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> xdist(1, lCDim[0]);
    uniform_int_distribution<int> ydist(1,lCDim[1]);
    array<int, 2> rPos = {xdist(gen), ydist(gen)};
    return rPos;
}

void check_bounds(array<int, 2> pos, array<int, 2> cDim, bool *ptr) {
    if (pos[0] >= 0 && pos[0] <= cDim[0] && pos[1] >= 0 && pos[1] <= cDim[1]) {
        *ptr = true;
    } else {
        *ptr = false;
    }
    return;
}

bool check_same_location(array<int, 2> pos1, array<int, 2> pos2) {
    if (pos1 == pos2) { 
        return true;
    } else {
        return false;
    }
}

bool check_if_neighboring(array<int, 2> hpos, array<int, 2> objpos) {
    if (hpos[1] == objpos[1] && (hpos[0] + 1 == objpos[0] || hpos[0] - 1 == objpos[0])) {
        return true; // checking to the east and west
    } else if (hpos[0] == objpos[0] && (hpos[1] + 1 == objpos[1] || hpos[1] - 1 == objpos[1])) {
        return true; // checking north and south
    } else { // the two statements above could be combined into one, but it is easier to read this way
        return false;
    }
}

void get_size(array<int, 2> *cDimptr) {
    array<int, 2> dims = {0, 0};
    do {
        cout << "Please enter the desired x-dimension of your cave: "; cin >> dims[0];
        cout << "Please enter the desired y-dimension of your cave: "; cin >> dims[1];
    } while (dims[0] < 6 || dims[1] < 6);
    *cDimptr = dims;
    return;
}
/* the below was a bad implementaion, and idea tbh
void gen_world(array<int, 2> *cDimptr, array<int, 2> *hposptr, array<int, 2> *p1posptr, array<int, 2> *p2posptr, array<int, 2> *b1posptr, array<int, 2> *b2posptr, array<int, 2> *wposptr) {
    array<int, 2> lCDim = *cDimptr;
    array<array<int, 3>, 6> occupiedPosArray = {{{0,0,0}}, {{0,0,0}}, {{0,0,0}}, {{0,0,0}}, {{0,0,0}}, {{0,0,0}}};
    bool validArray = false;
    do {
        int i = 0;
        for (array<int, 3> pos : occupiedPosArray) {
            array<int, 2> rnd = random_position(lCDim);
            cout << "(" << rnd[0] << "," << rnd[1] << ")" << endl;
            pos = {rnd[0], rnd[1], rnd[0]+rnd[1]};
            for (int j = i-1; j >= 0; j--) {
                
                if (pos[3] == occupiedPosArray[j][3] && pos[0] == occupiedPosArray[j][0] && pos[1] == occupiedPosArray[j][1]) {
                    // come to think of it, I definitly could've just made an array sum function to test
                        // I figured that doing it this way would be faster, but perhaps summing them all 
                        // is a deoptimization, lol
                    cout << pos[3] << occupiedPosArray[j][3];
                    cout << pos[1] << occupiedPosArray[j][1];
                    cout << pos[2] << occupiedPosArray[j][2];
                    validArray = false;
                }
            }
            i++;
        }
    } while (!validArray);
    if(validArray) {
        for (array<int, 3> pos : occupiedPosArray) {
            cout << "(";
            for (int sPos : pos) {
                cout << sPos << ", ";
            }
            cout << ")" << endl;
        }
    } else {cout << "fail";}
    
}
*/
void gen_world(array<int, 2> *cDimptr, array<int, 2> *hposptr, array<int, 2> *p1posptr, array<int, 2> *p2posptr, array<int, 2> *b1posptr, array<int, 2> *b2posptr, array<int, 2> *wposptr) {
    array<int, 2> lCDim = *cDimptr;
    array<array<int, 2>, 6> randomPosArray;
    bool validArray;
    do {
        validArray = true;
        for(int i = 0; i < 6; i++) {
            randomPosArray[i] = random_position(lCDim);
        }
        int i = 0;
        for (array<int, 2> pos : randomPosArray) {
            for (int j = i-1; j >= 0; j--) {
                //cout << "i: " << i << endl;
                //cout << "j: " << j << endl;
                //cout << "pos: (" << pos[0] << ", " << pos[1] << ")" << endl;
                //cout << "rpos: (" << randomPosArray[j][0] << ", " << randomPosArray[j][1] << ")" << endl;
                if (pos[0] == randomPosArray[j][0] && pos[1] == randomPosArray[j][1]) {
                    //cout << "redo" << endl;
                    validArray = false;
                }
            }
            i++;
        }
        } while (!validArray);
    //cout << "Hunter: (" << randomPosArray[0][0] << ", " << randomPosArray[0][1] << ")" << endl;
    //cout << "Pit 1: (" << randomPosArray[1][0] << ", " << randomPosArray[1][1] << ")" << endl;
    //cout << "Pit 2: (" << randomPosArray[2][0] << ", " << randomPosArray[2][1] << ")" << endl;
    //cout << "Bat 1: (" << randomPosArray[3][0] << ", " << randomPosArray[3][1] << ")" << endl;
    //cout << "Bat 2: (" << randomPosArray[4][0] << ", " << randomPosArray[4][1] << ")" << endl;
    //cout << "Wumpus: (" << randomPosArray[5][0] << ", " << randomPosArray[5][1] << ")" << endl;
    *hposptr = randomPosArray[0];
    *p1posptr = randomPosArray[1];
    *p2posptr = randomPosArray[2];
    *b1posptr = randomPosArray[3];
    *b2posptr = randomPosArray[4];
    *wposptr = randomPosArray[5];
    return;

}

char player_decision() {
    char pInput;
    bool badInput;

    do {
        badInput = false;
        cout << "Would you like to move or shoot? (M/S)?"; cin >> pInput;
        if (tolower(pInput) != 'm' && tolower(pInput) != 's') {
            badInput = true;
            cout << endl << "That input wasn't understood, try again." <<  endl;
        }
    } while (badInput);
    return pInput;
}

void player_move(array<int, 2> *hposptr, array<int, 2> *cDimptr) {
    array<int, 2> hpos = *hposptr;
    array<int, 2> cDim = *cDimptr;
    array<int, 2> newPos;
    char pInput;
    int x, y;
    bool badInput;
    bool goodMove = false;
    bool *goodMoveptr = &goodMove;
    do {
        badInput = false;
        cout << "Which direction would you like to move? (N, E, S, W) :"; cin >> pInput;
        if (tolower(pInput) == 'e') {
            newPos = {hpos[0]+1, hpos[1]};
            check_bounds(newPos, cDim, goodMoveptr);
        } else if (tolower(pInput) == 'w') {
            newPos = {hpos[0]-1, hpos[1]};
            check_bounds(newPos, cDim, goodMoveptr);
        } else if (tolower(pInput) == 'n') {
            newPos = {hpos[0], hpos[1]+1};
            check_bounds(newPos, cDim, goodMoveptr);
        } else if (tolower(pInput) == 's') {
            newPos = {hpos[0], hpos[1]-1};
            check_bounds(newPos, cDim, goodMoveptr);
        } else if (tolower(pInput) == 't') {
            cout << "You choose to teleport, choose your new location."; cin >> x; cin >> y;
            newPos = {x, y};
            check_bounds(newPos, cDim, goodMoveptr);
        } else { 
            badInput = true;
            cout << endl << "Your input wasn't understood, try again." << endl;
        }
        if (!goodMove) {
            cout << endl << "You cannot move in that direction, try again." << endl;
        }
    } while(badInput || !goodMove);
    *hposptr = newPos;
    cout << "Hunter: (" << newPos[0] << ", " << newPos[1] << ")" << endl;
    return;
}

bool player_shoot(array<int, 2> *hposptr, array<int, 2> *wposptr, array<int, 2> *cDimptr) {
    array<int, 2> hpos = *hposptr;
    array<int, 2> wpos = *wposptr;
    array<int, 2> apos = hpos;
    bool badInput;
    bool hit = false;
    bool noHitWall = true;
    char pInput;
    int x = 0;
    int y = 0;
    do {
        badInput = false;
        cout << "Which direction would you like to shoot? (N, E, S, W) :"; cin >> pInput;
        if (tolower(pInput) == 'n') {
            y = 1;
        } else if (tolower(pInput) == 's') {
            y = -1;
        } else if (tolower(pInput) == 'e') {
            x = 1;
        } else if (tolower(pInput) == 'w') {
            x = -1;
        } else { 
            badInput = true;
            cout << endl << "Your input wasn't understood, try again." << endl;
        }
    } while(badInput);

    for (int i = 0; i < 6; i++) {
        apos[0] += x;
        apos[1] += y;
        hit += check_same_location(apos, wpos);
        //cout << "arrow_loc: " << apos[0] << "," << apos[1] << endl;
        check_bounds(apos, *cDimptr, &noHitWall);
    }
    if (!hit && noHitWall) {
        cout << "You hear your arrow clatter to the ground." << endl;
    } else if (!hit && !noHitWall) {
        cout << "You hear your arrow hit the cave wall." << endl;
    }
    return hit;
}

void move_object(array<int, 2> *objptr, array<int, 2> *cDimptr) {
    array<int, 2> newPos;
    array<int, 2> lCDim = *cDimptr;
    bool validPos = true;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rand(0, 1);
    //who need if else statements anyways
    do {
        newPos = *objptr;
        newPos[rand(gen)] += 1 - 2 * rand(gen); // randomly generates a movement in the x or y direction
        check_bounds(newPos, lCDim, &validPos);
    } while (!validPos);
    *objptr = newPos;
    return;
}

void check_nearby(array<int, 2> *hposptr, array<int, 2> *p1posptr, array<int, 2> *p2posptr, array<int, 2> *wposptr) {
    if (check_if_neighboring(*hposptr, *p1posptr) || check_if_neighboring(*hposptr, *p2posptr)) {
        cout << "You feel a strong breeze pass you by." << endl;
    }
    if (check_if_neighboring(*hposptr, *wposptr)) {
        cout << "You smell a foul stench." << endl;
    }
    return;
}

void check_player_tile(bool *hAlive, int *wAlive, array<int, 2> *cDimptr, array<int, 2> *hposptr, array<int, 2> *p1posptr, array<int, 2> *p2posptr, array<int, 2> *b1posptr, array<int, 2> *b2posptr, array<int, 2> *wposptr) {
    bool resolvedMove = false;
    do {
        if (check_same_location(*hposptr, *wposptr)){
            // wumpus death
            *wAlive = 1;
            *hAlive = false;
            resolvedMove = true;
        } else if ((check_same_location(*hposptr, *p1posptr) || check_same_location(*hposptr, *p2posptr)) && !(check_same_location(*hposptr, *b1posptr) || check_same_location(*hposptr, *b2posptr))) {
            // pit death
            *wAlive = -1;
            *hAlive = false;
            resolvedMove = true;
        } else if ((check_same_location(*hposptr, *p1posptr) || check_same_location(*hposptr, *p2posptr)) && (check_same_location(*hposptr, *b1posptr) || check_same_location(*hposptr, *b2posptr))) {
            // nearly a pit death, a bat saved you
            cout << "You take a step and feel nothing." << endl;
            cout << "You begin to fall." << endl;
            cout << "You hear a fluttering as a bat picks you up and moves you to an new location, thus saving your life." << endl;
            *hposptr = random_position(*cDimptr);
        } else if (check_same_location(*hposptr, *b1posptr) || check_same_location(*hposptr, *b2posptr)) {
            //just bats
            cout << "You hear a fluttering as a bat picks you up and moves you to an new location." << endl;
            *hposptr = random_position(*cDimptr);
        } else {
            resolvedMove = true;
        }
    } while (!resolvedMove);
}

void play_game() {

    array<int, 2> cDim, hPos, p1Pos, p2Pos, b1Pos, b2Pos, wPos;

    array<int, 2> *cDimptr = &cDim;
    array<int, 2> *hposptr = &hPos;
    array<int, 2> *p1posptr = &p1Pos;
    array<int, 2> *p2posptr = &p2Pos;
    array<int, 2> *b1posptr = &b1Pos;
    array<int, 2> *b2posptr = &b2Pos;
    array<int, 2> *wposptr = &wPos;

    bool hAlive = true;
    int wAlive = 1;

    bool *hAliveptr = &hAlive;
    int *wAliveptr = &wAlive;

    //setup and dialogue
    cout << "Hello," << endl;
    cout << "Welcome to Hunt the Wumpus!" << endl;
    cout << "You, sadly, are blind, but you have a keen sense of smell." << endl;
    cout << "But, here you are, in a cave, with a Wumpus, a pit, and a bat." << endl;
    cout << "You have been tasked with killing said wumpus." << endl;
    cout << "Hopefully, you don't die trying." << endl;
    cout << "Luckily, you get to choose how large the cave is, as every cave has a wumpus and we here have a huge variety of caves." << endl;
    cout << "Due to the nature of nature here caves only generate with a minimum size of 6x6 unspecified units." << endl;
    get_size(cDimptr);
    cout << "Your cave is of dimensions (" << cDim[0] << ", " << cDim[1] << ")." << endl;
    gen_world(cDimptr, &hPos, p1posptr, p2posptr, b1posptr, b2posptr, wposptr);



    do {
        cout << "Hunter: (" << hPos[0] << ", " << hPos[1] << ")" << endl;
        //cout << "Pit 1: (" << p1Pos[0] << ", " << p1Pos[1] << ")" << endl;
        //cout << "Pit 2: (" << p2Pos[0] << ", " << p2Pos[1] << ")" << endl;
        //cout << "Bat 1: (" << b1Pos[0] << ", " << b1Pos[1] << ")" << endl;
        //cout << "Bat 2: (" << b2Pos[0] << ", " << b2Pos[1] << ")" << endl;
        //cout << "Wumpus: (" << wPos[0] << ", " << wPos[1] << ")" << endl;

        check_nearby(hposptr, p1posptr, p2posptr, wposptr);

        if (tolower(player_decision()) == 'm') {// does player move or shoot?
            player_move(hposptr, cDimptr);
        } else {
            if (player_shoot(hposptr, wposptr, cDimptr)) {
                wAlive = false;
            }
        }

        check_player_tile(hAliveptr, wAliveptr, cDimptr, hposptr, p1posptr, p2posptr, b1posptr, b2posptr, wposptr);

        //Bat and wumpus move
        move_object(wposptr, cDimptr);
        move_object(b1posptr, cDimptr);
        move_object(b2posptr, cDimptr);

        //Location checks 
            //exa
        check_player_tile(hAliveptr, wAliveptr, cDimptr, hposptr, p1posptr, p2posptr, b1posptr, b2posptr, wposptr);


    }while(hAlive && wAlive); 
    //game end
        //if win
        //if loss
    if(hAlive) {
        cout << "You hear a wet thunk!" << endl << "You have hit the Wumpus!" << endl;
        cout << "Bright flood lights flicker on, blinding you." << endl;
        cout << "You hear 'Game over, you won!' emanating from the walls." << endl;
        cout << "For a moment you are very confused." << endl;
        cout << "As you realize that something is very wrong, you feel a sudden piercing pain in your neck and everything fades to black." << endl;
        cout << "You forget everything.";
    } else {
        if (wAlive == -1) { //pit death
            cout << "You take a step and feel a distinct lack of ground beneath you." << endl;
            cout << "You fall into a pit and starve to death." << endl;
            cout << "Game over.";
        } else { //wumpus death
            cout << "You hear a flurry of motion as a terrible smell engulfs you." << endl;
            cout << "The wumpus has found you and quickly devours you." << endl;
            cout  << "Game over.";
        }
    }
}   