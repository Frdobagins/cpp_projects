/* CSCI 200: Assignment 1: A1 - Random Encounter RPG
 *
 * Author: Hiram Despain
 * 
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     //Used Office Hours to review best practice and styling requirements
 *
 *  A1: This project is a simple terminal-based dungeon crawler.
 *      The player explores a dungeon and tries to collect enough gold to leave without dying to the monsters
 *      There is a large amount of dialogue.
 *      I also have left large sections of commented out code to preserve some of the other ideas I tried
 *      and then discarded.
*/


// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <map> //For monster info
#include <random> //For the dice rolling
#include <string> // also to store monster info
#include <vector> //also to store monster info

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;


/*
// Define any constants below this comment.
const vector<vector<any>> mobList = {{"an orc."  , "D8" , 8 , "You killed the orc!"   , },
                                     {"a goblin.", "D12", 12, "You killed the goblin!", },
                                     {"a dragon.", "D20", 20, "You slayed the dragon!", }};
                                       //type     die   #die     kill_text

const array<string, 3> monsterType = {};
const array<string, 3> diestr = {"D8", "D12", "D20"};
const array<int, 3>    dieNum = {8, 12, 20};
const array<string, 3> killText = {};
const array<string, 3> ;
const array<string, 3> okay; */

/*
const vector<any> mobStats[] = {
    {15, 25, 50}, //hp
    {8, 12, 20}, //die
    {1, 5, 10}, //dmgMin
    {5, 10, 15}, //dmgMax
    {"D8", "D12", "D20"}, //sDie
    {"You encounter an orc.", "You encounter a goblin with 25 HP.", "You encounter a dragon."}, //encounterText
    {"The Orc slays you with your sword. Game over.", "The goblin slays you with his sword. Game Over.", "You slayed the dragon!"}, //fightKillText
    {"The orc hits you in the back with an arrow. Game Over.", "You fall into a trap dug by the goblin. Game Over.", "The dragon's flame burns you to a crisp. Game Over."}, //sneakKillText
    {"You killed the orc!", "You killed the goblin!", "The dragon gobbled you up. Game Over."}, //deathText
    {"You sneak past the orc unaware.", "You sneak past the goblin unaware.", "You escaped the dragon's lair."} //sneakPastText
};*/


//These maps are used to store the info about the different types of monsters 
//This one stores the numbers associated with them 
map<string, vector<int>> mobNumStats = {
    // 0 - Dragon
    // 1 - Orc
    // 2 - Goblin
    // 3 - Player (if applicable)
    { "hp"     , {50, 15, 25}}, //hp
    { "die"    , {20, 8, 12}}, //die
    { "dmgMin" , {10, 1, 5, 5}}, //dmgMin 
    { "dmgRange" , {5, 4, 5, 10}}, //dmgRange
    { "hitThreshold" , {17, 2, 4}}, //inclusive also is used for the run threshold
    { "goldRange" , {20, 8, 12}}, //The amount of gold possible
};
//This one stores the strings associated with them
map<string, vector<string>> mobStrStats = {
    { "sDie"   , {"D20", "D8", "D12"}}, //sDie
    { "monsterType"   , {"dragon", "orc", "goblin"}}, //Name of the monster
    { "encounterText" , {"You encounter a dragon.", "You encounter an orc.", "You encounter a goblin."}}, //encounterText
    { "sneakKillText", {"The dragon's flame burns you to a crisp.", "The orc hits you in the back with an arrow.", "You fall into a trap dug by the goblin."}}, //sneakKillText
    { "fightKillText" , {"The dragon gobbled you up.", "The Orc slays you with your sword.", "The goblin slays you with his sword."}}, //fightKillText
    { "deathText"     , {"You slayed the dragon!", "You killed the orc!", "You killed the goblin!"}}, //deathText
    { "sneakPastText" , {"You escaped the dragon's lair.", "You sneak past the orc unaware.", "You sneak past the goblin unaware."}} //sneakPastText
};


// Imma learn how to make a class in c++, it'll be less messy than this crap
/* I was so wrong about that it isn't any better, I don't know inheritance good enough
class Player {
    public:
        int hp = 100;
        int dmgMin = 5;
        int dmgMax = 15;


};

class monster {
};

class Orc : public monster{
    public:
        int hp = 15;
        int die = 8;
        int dmgMin = 1;
        int dmgMax = 5;
        string sDie = "D8";
        string encounterText = "You encounter an orc.";
        string fightKillText = "The Orc slays you with your sword. Game over.";
        string sneakKillText = "The orc hits you in the back with an arrow. Game Over.";
        string deathText     = "You killed the orc!";
        string sneakPastText = "You sneak past the orc unaware.";

};

class Goblin : public monster{
    public:
        int hp = 25;
        int die = 12;
        int dmgMin = 5;
        int dmgMax = 10;
        string sDie = "D12";
        string encounterText = "You encounter a goblin with 25 HP.";
        string fightKillText = "The goblin slays you with his sword. Game Over.";
        string sneakKillText = "You fall into a trap dug by the goblin. Game Over.";
        string deathText     = "You killed the goblin!";
        string sneakPastText = "You slip from the goblin's sight.";

};

class Dragon : public monster{
    public:
        int hp = 50;
        int die = 20;
        int dmgMin = 10;
        int dmgMax = 15;
        string sDie = "D20";
        string encounterText = "You encounter a dragon.";
        string fightKillText = "You slayed the dragon!";
        string sneakKillText = "The dragon's flame burns you to a crisp.  Game Over.";
        string deathText     = "The dragon gobbled you up.  Game Over.";
        string sneakPastText = "You escaped the dragon's lair.";

};*/


int roll_die(int dietype) {
    //"Rolls" a die
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rnd(0, dietype);
    return rnd(gen);
}


/* Here I was going to create separate functions for each type of encounter, but I decided that I wanted to use only one function
void orc_encounter() {
    cout << "You encounter an orc." << endl;
}

void goblin_encounter() {
    cout << "You encounter a goblin." << endl;
}

void dragon_encounter() {
    cout << "You encounter a dragon." << endl;

}

void encounter_gen() {
    switch (roll_die(8)) {
        case 1: case 4: case 7:
            orc_encounter();
            break;
        case 2: case 5: case 8:
            goblin_encounter();
            break;
        case 3: case 6:
            dragon_encounter();
            break;
        default:
            break;
    }
}
*/

/* I don't know enough about OOP in c++ to use the inheritance correctly and create a function that calls text from a subclass.
Orc  orc;
void encounter(orc) {
    cout << monster.encounterText << "text" << endl;
}
*/


int dmg(int mobId) {
    //Generates a int amount of dmg based off the monster's dmg minimum and dmg range
    return (roll_die(mobNumStats["dmgRange"][mobId]) + mobNumStats["dmgMin"][mobId]);
}


int gen_fight_loot(int monsterGold) {
    //Generates the loot found after a fight
    int lootFound = roll_die(monsterGold) + roll_die(monsterGold);
    cout << "You found " << lootFound << " gold!" << endl;
    return (lootFound);
}


int gen_empty_loot() {
    //Gives loot in an empty room
    int lootFound = 1;
    cout << "You found " << lootFound << " gold!" << endl;
    return (lootFound);
}

vector<int> gen_encounter(int playerHp) {
    //This determines the monster and then runs the player through the encounter
    char userInput = 'z';
    bool fight;
    int goldFound = 0; //is returned at the end of the function and added to the gold total
    int deathType = 0; //returns a 1 or a 0 depending on how the player died, it need to be an int because of the vector type
    int dmgTaken = 0;  //very similar to the gold found variable
    int mobId = roll_die(8) % 3; //0 = drag, 1 = orc, 2 = gob
    int mobHp = mobNumStats["hp"][mobId]; 
    cout << (mobStrStats["encounterText"][mobId]) << endl;
    cout << "Would you like to know more about the " << (mobStrStats["monsterType"][mobId]) << "? (enter y to accept)"; cin >> userInput;
    if(tolower(userInput) == 'y') { //if the user wants to know the monster's stats
        cout << "The " << mobStrStats["monsterType"][mobId] << " has " << mobHp << " health!" << endl;
        cout << "You need to roll an " << mobNumStats["hitThreshold"][mobId] << " or higher on a " << mobStrStats["sDie"][mobId] << " to hit the " << mobStrStats["monsterType"][mobId] << "!" << endl;
        cout << "When you miss an attack against the " << mobStrStats["monsterType"][mobId] << ", the " << mobStrStats["monsterType"][mobId] << " will deal between " << mobNumStats["dmgMin"][mobId] << " and " << (mobNumStats["dmgMin"][mobId] + mobNumStats["dmgRange"][mobId]) << " damage to you!" << endl;
    }
    cout << "Do you wish to (f)ight or (r)un?"; cin >> userInput;
    if(tolower(userInput) == 'f') {
        fight = true;
    } else {
        fight = false;
    }

    while(mobHp > 0 && playerHp > dmgTaken && fight) { 
        //player attack -- stays in the loop until the mob dies, the player dies, or the player flees.
        int hitAttempt = roll_die(mobNumStats["die"][mobId]);
        int dmgDealt;
        char continuefight; //used to receive input from the player
        cout << endl;
        cout << "You rolled a " << hitAttempt << " on a " << mobStrStats["sDie"][mobId] << "!" << endl;
        if(hitAttempt >= mobNumStats["hitThreshold"][mobId]) { //Checks for a hit on the monster
            dmgDealt = dmg(3); //3 is player
            mobHp -= dmgDealt;
            cout << "You hit the " << mobStrStats["monsterType"][mobId] << "!" << endl;
            cout << "You dealt " << dmgDealt << " damage." << endl;
            if(mobHp > 0) { //if it dies, this dialogue is skipped
                cout << "The " << mobStrStats["monsterType"][mobId] << " has " << mobHp << " health remaining." << endl;
            }
        } else { //if the player doesn't hit the monster he gets hit
            dmgDealt = dmg(mobId); 
            dmgTaken += dmgDealt;
            cout << "You missed your attack." << endl;
            cout << "In retaliation, the " << mobStrStats["monsterType"][mobId] << " attacks you!" << endl;
            cout << "You take " << dmgDealt << " damage!" << endl;
            if(dmgDealt < playerHp) { //skips dialogue if the player dies to the attack
                cout << "You have " << (playerHp - dmgTaken) << " health left!" << endl;
                cout << "Do you wish to continue the fight? (enter n to decline)" << endl;
                cout << "Beware, the " << mobStrStats["monsterType"][mobId] << " will hit you again as you run." << endl; cin >> continuefight;
                if(tolower(continuefight) == 'n') { //checks if the player wants to flee
                    fight = false;
                }
            }
        }
    }
    if(!fight) { //If the player decided to flee before or during the fight
        deathType = 1;
        if(roll_die(mobNumStats["die"][mobId]) >= mobNumStats["hitThreshold"][mobId]) { //does the monster hit?
            int dmgDealt = dmg(mobId);
            dmgTaken += dmgDealt;
            cout << "The " << mobStrStats["monsterType"][mobId] << " hits you!" << endl;
            cout << "You take " << dmgDealt << " damage!" << endl;
            if(dmgDealt < playerHp) { //if the player is still alive, prints the below
                cout << "You have " << (playerHp - dmgTaken) << " health left!" << endl;
            }
        } else {
            cout << mobStrStats["sneakPastText"][mobId] << endl;
        }
    }
    if(mobHp <= 0) { //if the monster died during the fight, the below happens
        cout << mobStrStats["deathText"][mobId] << endl;
        goldFound = gen_fight_loot(mobNumStats["goldRange"][mobId]);
    }
    return {dmgTaken, goldFound, mobId, deathType};
        //mobId is used to generate the gold later on
        //deathType is used to determine the type of death text used, 0 is death in fight, 1 is a death while fleeing
}


bool gen_new_room() { //a much smaller function that check if the room has a monster or not in it
    /*switch (roll_die(6)) {
        case 1: case 2: case 4: case 5:
            cout << "There's an enemy in the room!" << endl;
            //encounter_gen();
            break;
        case 3: case 6:
            cout << "You slip through the room." << endl;
            break;
        default:
            break;
    }*/
    cout << "You enter a new room." << endl;
   if(roll_die(6) % 3 == 0) {
    cout << "There is nothing in the room!" << endl;
    return false;
   } else {
    cout << "There's an enemy in the room!" << endl;
    return true;
   }
}

// Must have a function named "main", which is the starting point of a C++ program.
int main() {
    char playerChoice; //used to register player input
    int playerHp = 100; //starting health
    int gold = -100; //The starting debt of the player
    vector<int> encounterOutcome;

    //intro
    //player is set into the dungeon to repay a debt or die trying, as soon as sufficient gold is collected, they run.
    //if they bring extra it will be confiscated, if they try to hid it, they are found out and sent in again.
    //This is here just to hide the dialogue
    cout << endl << endl << endl;
    cout << "    --You managed to offend a nobleman while working as a guard.--" << endl;
    cout << "    --For your 'crime' you have a 'choice', repay the debt or die.--" << endl;
    cout << "    --Luckily for you, the nobleman has graciously provided you with a way to quickly repay your debt.--" << endl;
    cout << "    --There is a dungeon on the outskirts of town that is filled with treasure.--" << endl;
    cout << "    --You arrive at the entrance to the dungeon.--" << endl;
    cout << "    --The dungeon master greets you.--" << endl;
    cout << "Hello, welcome to the endless dungeon!" << endl;
    cout << "You're here to repay your debt, right?" << endl;
    cout << "    --The guard nods and hands him a paper--" << endl;
    cout << "All you need to do is go in there and collect 100 gold pieces!" << endl;
    cout << "Pretty easy, right?" << endl;
    cout << "    --the dungeon master chuckles and opens the gate to the dungeon--" << endl;
    cout << "Do you wish to enter? (y/n) "; cin >> playerChoice;
    cout << "Perhaps I should've told you earlier, but here any response is taken as a yes!" << endl;
    cout << "The freedom to choose is really important to me!" << endl;
    cout << "I'm not a monster..." << endl;
    cout << "    --He smiles and gestures to the entrance--" << endl;
    cout << "Do you enter? (s/d) "; cin >> playerChoice;
    cout << "    --You begin to enter the dungeon.--" << endl;
    cout << "Oh, wait, I almost forgot, here's your armor and sword!" << endl;
    cout << "Do you take them? (y)"; cin >> playerChoice;
    cout << "Oh, didn't you know? There's a bunch of monsters down there." << endl;
    cout << "    --He has a scary twinkle in his eye--" << endl;
    cout << "It's dangerous to go alone, take them." << endl;
    cout << "    --He says that to you as he tosses them on the ground just inside the entrance--" << endl;
    cout << "Do you pick them up? (if you haven't realized it doesn't matter what you type rn)"; cin >> playerChoice;
    cout << "The guard pushes you inside and slams the door shut behind you." << endl;
    cout << "You pick up the sword and armor." << endl;
    cout << "    --You look around the entrance to the dungeon, it's dark and damp--" << endl;
    cout << "    --The dungeon master hands you a lit torch--" << endl;
    cout << "    --You see a single exit to the room--" << endl;

    int loopCounter = 0; //keeps track of how long they've stayed in the lobby
    do { //if they decide to leave the lobby
        loopCounter++;
        cout << "Do you wish to move to the next room? (y/n) "; cin >> playerChoice;
        cout << endl;
        if(tolower(playerChoice) == 'n') {
            switch (loopCounter) {
            case 1:
                cout << "    --You realize that you have no food--" << endl;
                cout << "    --The dungeon master looks at you--" << endl;
                cout << "You'd better get that gold before you starve!" << endl;
                break;
            case 3:
                cout << "    --The dungeon master chuckles--" << endl;
                cout << "You're not the first to try to starve themselves instead of enter" << endl;
                cout << "It never works out well." << endl;
                cout << "    --He points at some skeletons in the corner of the room.--" << endl;
                break;
            case 4:
                cout << "Welp, I gotta go get lunch, see ya later!" << endl;
                cout << "    --The dungeon master leaves--" << endl;
                break;
            case 10:
                cout << "    --The dungeon master returns with a sandwich.--" << endl;
                cout << "Oh, you're still here?" << endl;
                cout << "    --He goes into his little house and closes the door--" << endl;
                break;
            case 20:
                cout << "    --It gets dark outside--" << endl;
                cout << "    --Your torch begins to sputter and die--" << endl;
                break;
            case 25:
                cout << "The morning comes and the dungeon master returns." << endl;
                cout << "Wow, you're stubborn." << endl;
                cout << "I'm impressed." << endl;
                cout << "You want another torch?" << endl;
                cout << "    --He hands you another torch--" << endl;
                break;
            default:
                break;
            }
            if(loopCounter >= 30) {
                playerHp -= 10;
                if(playerHp <= 0) {
                    cout << "--You starved to death in the entryway of the dungeon.--" << endl;
                    cout << "--You failed to repay your debt.--" << endl;
                    cout << "--The dungeon master finds the smell of your decomposing body rather putrid.--" << endl;
                    cout << "Game Over :(";
                return 0; //ends game when the player dies 
                }
                cout << "Hunger gnaws at your stomach." << endl;
                cout << "You feel weak." << endl;
            }
        }
    } while(tolower(playerChoice) != 'y');


    while(playerHp > 0 && gold < 0) { //the main gameplay loop
        if(gen_new_room()) {
            encounterOutcome = gen_encounter(playerHp);
            playerHp -= encounterOutcome[0];
            gold += encounterOutcome[1];
        } else {
            gold += gen_empty_loot();
        }
        if(playerHp > 0) { //does the following if the player isn't dead
            cout << "Do you wish to move to the next room? (y/n) "; cin >> playerChoice;
            if(tolower(playerChoice) == 'n') {
                cout << "    --You go back to the entrance of the dungeon--" << endl;
                cout << "    --You ring a bell near the gate--" << endl;
                cout << "    --The dungeon master comes to the gate--" << endl;
                cout << "You're back already?" << endl;
                cout << "You have the gold? (y)" << endl; cin >> playerChoice;
                cout << "Well, you don't have enough, go back in there and get the gold!" << endl;
                cout << "    --You go back in--" << endl;
            }
        }
    }

    if(playerHp <= 0) { //if the player is dead
        if(!encounterOutcome[3]) { // if the player died in a fight
            cout << mobStrStats["fightKillText"][encounterOutcome[2]] << endl; //encounteroutcome[2] is mobId, its used to determine the type of text used when the player dies.
        } else { //if died when escaping
            cout << mobStrStats["sneakKillText"][encounterOutcome[2]] <<endl;
        }
        cout << "    --You died in the dungeon.--" << endl;
        cout << "    --You failed to repay your debt.--" << endl;
        cout << "Game Over." << endl;
    } else { //if the player wins
        cout << "    --You have collected 100 gold--" << endl;
        cout << "    --You have repaid your debt!--" << endl;
        cout << "    --The dungeon master greets you when you arrive at the gate and ring the bell.--" << endl;
        cout << "    --You hand him the gold and he counts it.--" << endl;
        cout << "    --You have " << gold << " gold left over!--" << endl;
        cout << "    --You have " << playerHp << " health left!--" << endl;
        cout << "You are free to go!" << endl;
        cout << "If you want to, you could stay and earn more gold!" << endl;
        cout << "What do you think? (y/n)"; cin >> playerChoice;
        cout << "You leave with your freedom" << endl;
        cout << "Game Over." << endl;
        if(tolower(playerChoice) == 'y') {
            cout << "What? Don't you remember what I said earlier? Freedom of choice is super important to me!" << endl;
            cout << "If you really wanna play again, just restart the program." << endl;
        }
    }
  return 0;
}