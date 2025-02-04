#ifndef WUMPUS_FUNCTIONS_H
#define WUMPUS_FUNCTIONS_H

#include <array>
#include <map>
#include <string>

using namespace std;

/**
 * @brief Generates a random position given cave size
 * 
 * @param caveSize 
 * @param newPosStore where the random position is to be stored
 */
void random_position(array<int, 2> caveSize, array<int, 2> *pNewPos);

/**
 * @brief debugging, prints out all locations
 * 
 * @param lmap local map 
 */
void print_locations(map<string, array<int, 2>> lmap);

/**
 * @brief makes sure the provided position is in the world
 * 
 * @param caveSize ...
 * @param newPos position to check
 * @return true inbounds
 * @return false out of bounds
 */
bool check_bounds(array<int, 2> caveSize, array<int, 2> newPos);

/**
 * @brief checks if two objects are in the same location
 * 
 * @param object1 x & y of obj1
 * @param object2 x & y of obj2
 * @return true same location
 * @return false not same location
 */
bool check_same_location(array<int, 2> object1, array<int, 2> object2);

/**
 * @brief checks if there is something nearby
 * 
 * @param hunterPos position of hero
 * @param objectPos position of obj
 * @return true is neighboring
 * @return false not
 */
bool check_if_neighboring(array<int, 2> hunterPos, array<int, 2> objectPos);

/**
 * @brief get world size from user
 * 
 * @param pCaveSize where world size is stored
 */
void get_size(array<int, 2> *pCaveSize);

/**
 * @brief generates random positions for all positions
 * 
 * @param pWorldMap a pointer to the worldmap, so that it can be edited
 */
void gen_world(map<string, array<int, 2>> *pWorldMap);

/**
 * @brief prompts the user of a choice between moving and shooting
 * 
 * @return char 
 */
char hero_choice();

/**
 * @brief moves hero in the requested direction
 * 
 * @param caveSize size of cave
 * @param phunterPos pointer to the hunter position 
 */
void move_hero(array<int, 2> caveSize, array<int, 2> *phunterPos);

/**
 * @brief processes the player's shot
 * 
 * @param caveSize cave size
 * @param hunterPos position of hunter
 * @param wumpusPos position of wumpus
 * @param pWumpusAlive pointer to wumpus life indicator
 */
void hero_shoot(array<int, 2> caveSize, array<int, 2> hunterPos, array<int, 2> wumpusPos, bool *pWumpusAlive);

/**
 * @brief moes an object by 1 in any direction
 * 
 * @param caveSize size of cave
 * @param objectPos pointer to object position
 */
void move_object(array<int, 2> caveSize, array<int, 2> *pObjectPos);

/**
 * @brief check the tiles near the player
 * 
 * @param lWorldMap 
 */
void check_nearby(map<string, array<int, 2>> lWorldMap);

/**
 * @brief checks if player is touching anything and if the player is dead
 * 
 * @param lWorldMap world map
 * @param pHunterPos pointer to hunter position (can be moved by bat)
 * @param pHunterDead hunter life indicator
 */
void check_player_tile(map<string, array<int, 2>> lWorldMap, array<int, 2> *pHunterPos, int *pHunterDead);

/**
 * @brief gameplay loop
 * 
 */
void play_game();

#endif