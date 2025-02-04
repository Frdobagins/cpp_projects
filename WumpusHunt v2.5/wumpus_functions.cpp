#include "wumpus_functions.h"

#include <array>
#include <iostream>
#include <map>
#include <random>
#include <string>
using namespace std;

random_device rd;
mt19937 gen(rd());

void random_position(array<int, 2> caveSize, array<int, 2> *pNewPos) {
    uniform_int_distribution<int> xdist(1, caveSize[0]);
    uniform_int_distribution<int> ydist(1,caveSize[1]);
    *pNewPos = {xdist(gen), ydist(gen)};
    return;
}

void print_locations(map<string, array<int, 2>> lmap) {
    for(auto entry : lmap) {
        cout << entry.first << ": {" << entry.second[0] << ", " <<  entry.second[1] << "}" << endl;
    }
    return;
}

bool check_bounds(array<int, 2> caveSize, array<int, 2> newPos) {
    return (caveSize[0] >= newPos[0] && caveSize[1] >= newPos[1] && newPos[0] > 0 && newPos[1] > 0);
}

bool check_same_location(array<int, 2> object1, array<int, 2> object2) {
    return (object1 == object2);
}

bool check_if_neighboring(array<int, 2> hunterPos, array<int, 2> objectPos) {
    bool neighboring = false;
    neighboring += check_same_location({hunterPos[0]++, hunterPos[1]}, {objectPos[0], objectPos[1]});
    neighboring += check_same_location({hunterPos[0]--, hunterPos[1]}, {objectPos[0], objectPos[1]});
    neighboring += check_same_location({hunterPos[0], hunterPos[1]++}, {objectPos[0], objectPos[1]});
    neighboring += check_same_location({hunterPos[0], hunterPos[1]--}, {objectPos[0], objectPos[1]});
    return neighboring;
}

void get_size(array<int, 2> *pCaveSize) {//FUTURE: make it so it only accept ints
    array<int, 2> userDimensions = {0, 0};
    do { //warning, this throws an infinite loop if a number isn't entered. 
        // luckily, for this project, we assume they will enter a number
        cout << "Please enter the desired x-dimension of your cave: "; cin >> userDimensions[0];
        cout << "Please enter the desired y-dimension of your cave: "; cin >> userDimensions[1];
    } while (userDimensions[0] < 6 || userDimensions[1] < 6);
    *pCaveSize = userDimensions;
    return;
}

void gen_world(map<string, array<int, 2>> *pWorldMap) {
    map<string, array<int, 2>> newWorldMap = *pWorldMap;
    bool badArray;
    do {
        badArray = false;
        for(auto &object : newWorldMap) { // generate a new random map -- I don't love using auto here, but I think its the best option 
            if(object.first != "CaveSize") {
                random_position(newWorldMap["CaveSize"], &object.second);
            }
        }
        for (auto object1 : newWorldMap) { //compares values in the map checking for duplicates
            for (auto object2 : newWorldMap) {
                badArray += (object1.first != object2.first) && (object1.second == object2.second);
            }
        }
    } while (badArray);
    *pWorldMap = newWorldMap;
    return;

}

char hero_choice () {
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

//pointer for hero location, array for world dims
void move_hero(array<int, 2> caveSize, array<int, 2> *pHunterPos) {
    map<char, array<int, 2>> inputMap = {
        {'n', {0, 1}},
        {'s', {0, -1}},
        {'e', {1, 0}},
        {'w', {-1, 0}}
    };
    array<int, 2> newPos;
    char pInput;
    bool badInput;
    bool badMove;

    do {
        badInput = false;
        badMove  = false;
        newPos = *pHunterPos;
        cout << "Which direction would you like to move? (N, E, S, W) :"; cin >> pInput;
        if(inputMap.find(pInput) != inputMap.end()) {
            newPos[0] += inputMap[pInput][0];
            newPos[1] += inputMap[pInput][1];
        } else {
            cout << endl << "Your input wasn't understood, try again." << endl;
            badInput = true;
        }
        if (!check_bounds(caveSize, newPos)) {
            cout << endl << "You cannot move in that direction, try again." << endl;
            badMove = true;
        }
    } while(badInput || badMove);
    *pHunterPos = newPos;
    return;
}

void hero_shoot(array<int, 2> caveSize, array<int, 2> hunterPos, array<int, 2> wumpusPos, bool *pWumpusAlive) {
    map<char, array<int, 2>> inputMap = {
        {'n', {1, 1}},
        {'s', {1, -1}},
        {'e', {0, 1}},
        {'w', {0, -1}},
    };
    bool badInput = false;
    bool hitWumpus = false;
    bool hitWall = false;
    char pInput;
    array<int, 2> arrowPos = hunterPos;
    
    do{
        cout << "In which direction would you like to shoot? (N, E, W, S) : "; cin >> pInput;
        if (inputMap.find(pInput) != inputMap.end()) {
            for (int i = 0; i <=5; i++) {
                arrowPos[inputMap[pInput][0]] += inputMap[pInput][1];
                hitWumpus += check_same_location(arrowPos, wumpusPos);
                hitWall += check_bounds(caveSize, arrowPos);
            }
        } else {
            cout << endl << "Your input wasn't understood, try again." << endl;
            badInput = true;
        }
    } while (badInput);
        if(hitWumpus) {
            *pWumpusAlive = false;
        } else if (hitWall) {
            cout << "You hear your arrow hit the cave wall." << endl;
        } else {
            cout << "You hear your arrow clatter to the ground." << endl;
        }
    return;
}

void move_object(array<int, 2> caveSize, array<int, 2> *pObjectPos) {
    array<int, 2> newPos;
    uniform_int_distribution<int> rand(0, 1);
    //who need if else statements anyways
    do {
        newPos = *pObjectPos;
        newPos[rand(gen)] += 1 - 2 * rand(gen); // randomly generates a movement in the x or y direction
    } while (!check_bounds(caveSize, newPos));
    *pObjectPos = newPos;
    return;
}

void check_nearby(map<string, array<int, 2>> lWorldMap) {
    if (check_if_neighboring(lWorldMap["Hunterpos"], lWorldMap["Pit1Pos"]) || check_if_neighboring(lWorldMap["Hunterpos"], lWorldMap["Pit2Pos"])) {
        cout << "You feel a strong breeze pass you by." << endl;
    }
    if (check_if_neighboring(lWorldMap["Hunterpos"], lWorldMap["WumpusPos"])) {
        cout << "You smell a foul stench." << endl;
    }
    return;
}

void check_player_tile(map<string, array<int, 2>> lWorldMap, array<int, 2> *pHunterPos, int *pHunterDead) {
    bool resolvedMove = false;

    do {
        if (check_same_location(lWorldMap["HunterPos"], lWorldMap["WumpusPos"])){
            // wumpus death
            *pHunterDead = 1;
            resolvedMove = true;
        } else if ((check_same_location(lWorldMap["HunterPos"], lWorldMap["Pit1Pos"]) || check_same_location(lWorldMap["HunterPos"], lWorldMap["Pit2Pos"])) && !(check_same_location(lWorldMap["HunterPos"], lWorldMap["Bat1Pos"]) || check_same_location(lWorldMap["HunterPos"], lWorldMap["Bat2Pos"]))) {
            // pit death
            *pHunterDead = -1;
            resolvedMove = true;
        } else if ((check_same_location(lWorldMap["HunterPos"], lWorldMap["Pit1Pos"]) || check_same_location(lWorldMap["HunterPos"], lWorldMap["Pit2Pos"])) && (check_same_location(lWorldMap["HunterPos"], lWorldMap["Bat1Pos"]) || check_same_location(lWorldMap["HunterPos"], lWorldMap["Bat2Pos"]))) {
            // nearly a pit death, a bat saved you
            cout << "You take a step and feel nothing." << endl;
            cout << "You begin to fall." << endl;
            cout << "You hear a fluttering as a bat picks you up and moves you to an new location, thus saving your life." << endl;
            random_position(lWorldMap["CaveSize"], &lWorldMap["HunterPos"]);
        } else if (check_same_location(lWorldMap["HunterPos"], lWorldMap["Bat1Pos"]) || check_same_location(lWorldMap["HunterPos"], lWorldMap["Bat2Pos"])) {
            //just bats
            cout << "You hear a fluttering as a bat picks you up and moves you to an new location." << endl;
            random_position(lWorldMap["CaveSize"], &lWorldMap["HunterPos"]);
        } else {
            resolvedMove = true;
        }
    } while (!resolvedMove);
    *pHunterPos = lWorldMap["HunterPos"];
    return;
}

void play_game() {
    map<string, array<int, 2>> worldMap = {
        //This stores all of the data, it is awesome, I no longer have to pass ten billion values to functions
        {"CaveSize", {0, 0}},
        {"HunterPos", {0, 0}},
        {"WumpusPos", {0, 0}},
        {"Pit1Pos"  , {0, 0}},
        {"Pit2Pos"  , {0, 0}},
        {"Bat1Pos"  , {0, 0}},
        {"Bat2Pos"  , {0, 0}},
    };
    bool wumpusAlive = true;
    int hunterDead = 0;

       //setup and dialogue
    cout << "Hello," << endl;
    cout << "Welcome to Hunt the Wumpus!" << endl;
    cout << "You, sadly, are blind, but you have a keen sense of smell." << endl;
    cout << "But, here you are, in a cave, with a Wumpus, a pit, and a bat." << endl;
    cout << "You have been tasked with killing said wumpus." << endl;
    cout << "Hopefully, you don't die trying." << endl;
    cout << "Luckily, you get to choose how large the cave is, as every cave has a wumpus and we here have a huge variety of caves." << endl;
    cout << "Due to the nature of nature here caves only generate with a minimum size of 6x6 unspecified units." << endl;
    get_size(&worldMap["CaveSize"]);
    cout << "Your cave is of dimensions (" << worldMap["CaveSize"][0] << ", " << worldMap["CaveSize"][1] << ")." << endl;
    gen_world(&worldMap);

    do {
        check_nearby(worldMap);

        if (tolower(hero_choice()) == 'm') {// does player move or shoot?
            move_hero(worldMap["CaveSize"], &worldMap["HunterPos"]);
        } else {
            hero_shoot(worldMap["CaveSize"], worldMap["HunterPos"], worldMap["WumpusPos"], &wumpusAlive);
        }

        check_player_tile(worldMap, &worldMap["HunterPos"], &hunterDead);

        //Bat and wumpus move
        move_object(worldMap["CaveSize"], &worldMap["WumpusPos"]);
        move_object(worldMap["CaveSize"], &worldMap["Bat1Pos"]);
        move_object(worldMap["CaveSize"], &worldMap["Bat2Pos"]);

        check_player_tile(worldMap, &worldMap["HunterPos"], &hunterDead);

    }while(wumpusAlive && !hunterDead); 

    if(!wumpusAlive) {
        cout << "You hear a wet thunk!" << endl << "You have hit the Wumpus!" << endl;
        cout << "Bright flood lights flicker on, blinding you." << endl;
        cout << "You hear 'Game over, you won!' emanating from the walls." << endl;
        cout << "For a moment you are very confused." << endl;
        cout << "As you realize that something is very wrong, you feel a sudden piercing pain in your neck and everything fades to black." << endl;
        cout << "You forget everything.";
    } else {
        if (hunterDead == -1) { //pit death
            cout << "You take a step and feel a distinct lack of ground beneath you." << endl;
            cout << "You fall into a pit and starve to death." << endl;
            cout << "Game over.";
        } else { //wumpus death
            cout << "You hear a flurry of motion as a terrible smell engulfs you." << endl;
            cout << "The wumpus has found you and quickly devours you." << endl;
            cout  << "Game over.";
        }
    }
    return;
}   