/* CSCI 200: Assignment 2 - Wumpus Hunt
* 
* Author: Hiram Despain
*
* Help used: n/a
*
* A2 - A game in which you hunt (or are hunted by) the wumpus. 
*
*
*/

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <string>
#include <random>

// Extra files
#include "wumpus_functions.h"

using namespace std;
// Define any constants below this comment.

// Must have a function named main, which is the starting point of a C++ program.

int main() {
    play_game();//contain the game loop

return 0; // signals the operating system that our program ended OK.
}