//2020 MrN00b0t solution to Codecademy Build a Text Adventure Project
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "adventure.hpp"

using namespace std;

//establish global objects and variables
//Making Players and Locations objects allows for ease of expansion
//For example, adding new player stats to allow random combats
//Ideally in future version also make items into objects to allow more functionality

Player player;
Location merchant("Cloaks and Daggers", { "1) Buy Thieves Tools (1gp)", "2) Buy Sword (4gp)", "3) Visit the Tavern", "4) Go on adventure!\n" }, "The merchant here sells simple weapons and tools.\nNothing too fancy but the quality is good.\n");
Location tavern("The Thirsty Ferret", { "1) Drink ale!", "2) Ask around for rumours", "3) Visit the Merchant", "4) Go on adventure!\n" }, "A very basic hostelry with straw on the floors.\nSeveral of the patrons are either highly inebriated, unconcious or fighting.\nThe ale seems reasonable and fairly priced.....\n");
Location crossroads("Crossroads", { "1) Visit the Undercrypt", "2) Enter the Maw of the Beast", "3) Investigate the Needletoe Caverns", "4) Return to safety\n" }, "Leaving town by the footpath, the well worn trail splits into three lesser travelled paths.\n");
Location undercrypt("Undercrypt", { "1) Fight the banshee", "2) Run away\n" }, "As you descend into the darkness of the crypt, you see a ghastly spectral visage floating towards you. As it nears, it emits a terrifying wail.\n");
Location needletoe_caverns("Needletoe Caverns", { "1) Fight the goblins", "2) Run away\n" }, "Picking your way through the tumbledown rockfalls of the cavern, you are set upon by a pack of snarling goblins, with vicious, long razor sharp finger and toe nails.\n");
Location maw_unknown("Maw", { "1) Step through the left portal", "2) Step through the right portal", "3) Search the area", "4) Return to safety\n" }, "You step through a cavern of tooth like stalactites into a short tunnel, at the end of which are two shimmering portals.\n");
Location maw_trapped("Maw Tunnel", { "1) Ignore the device and step through the left portal", "2) Ignore the device and step through the right portal", "3) Attempt to deactivate the device", "4) Return to safety\n"}, "You notice a small device embedded in the cavern wall, projecting a magical field across the tunnel between you and the two portals. There are piles of ash on the floor.\n");
Location maw_clear("Maw Tunnel - Disintegration device deactivated!", { "1) Step through the left portal", "2) Step through the right portal", "3) Return to safety\n" }, "The device has been deactivated. Two shimmering portals stand before you.\n");
Location dragon_lair("Dragons' Lair", { "1) Fight the dragon", "2) Flee in terror\n" }, "A huge winged beast sits atop a pile of treasure. As you step through the portal, it opens its fanged mouth. Molten lava drips from its' jaw.\nIt booms, 'You dare interrupt my slumber?'\n\n");
//set starting location
Location current_loc = tavern;

//define constructor and methods for Location

Location::Location(string new_name, vector<string> new_options, string new_description)
  : name(new_name), options(new_options), description(new_description){
  }

void Location::locate(){
    cout << "You are currently at:\n" + name +"\n\n";
}

void Location::describe() {
    cout << description + "\n";
}

void Location::show_options() {
    cout << "Will you:\n\n";
    for (string option : options) {
        cout << option + "\n";
    }
}

vector<string> Location::get_options() {
    return options;
}

string Location::get_name() {
    return name;
}

bool Location::is_clear() {
    return cleared;
}

void Location::clear() {
    cleared = true;
}

void Location::reset() {
    cleared = false;
}

//define constructor and methods for Player

Player::Player(string new_name, vector<string> new_inventory, int new_gold)
    : name(new_name), inventory(new_inventory), gold(new_gold) {

}

vector<string> Player::inv() {
    return inventory;
}

int Player::gp() {
    return gold;
}


void Player::show_inv() {

    cout << "\nYou have the following items in your inventory:\n";
    for (string item : inventory) {
        cout << item + "; ";
    }
    cout << "\n\nYou have " << gold << " gold.\n\n";

}

void Player::buy_item(string item, int cost) {

    if (cost > player.gp()) {

        cout << "\nYou do not have enough gold for that.\n\n";
        return;

    }

    else {

        cout << "\nYou buy the " << item << " for " << cost << " gold.";
        player.gold -= cost;
        player.inventory.push_back(item);
        player.show_inv();
        return;

    }

}

bool Player::check_inv(string item) {

    for (string thing : player.inventory) {

        if (thing == item) {
            return true;
        }
    }

    return false;
}

void Player::add_item(string item) {

    player.inventory.push_back(item);

}

void Player::reset() {

    player.gold = 5;
    player.inventory = { "Backpack" };

}

//define game functions

bool greeting(){

  string ready;
  cout << "\n******** Welcome to the Thirsty Ferret ********\n";
  cout << "**** Where adventure is just a pint away!! ****\n";
  cout << "\n";
  cout << "Drawn by tales of riches awaiting the bold, you have travelled to the village of Donbury.\n";
  cout << "Tired from your journey, you make your way to the village hub: The Thirsty Ferret Inn.\n\n";
  cout << "From any location, several choices will be available to you.\n";
  cout << "You need simply select your choice with the corresponding number.\n";
  cout << "You may also view your inventory at any time by typing INV.\n\n";
  cout << "Quit the game at any time by typing QUIT.\n\n";
  cout << "Good luck adventurer!\n\n";
  cout << "Enter Y when you are ready to begin your journey....\n";
  cout << "Any other key to exit\n";
  cin >> ready;
  if (ready == "y" || ready == "Y") {
      return true;
  }
  return false;
  
}

//random rumour generator that gives players hints about what they might face

string get_rumour() {

    srand(time(NULL));
    int rumour = rand() % 4;
    switch (rumour) {

    case 1:
        return "\nThe bartender says, 'They say The Undercrypt is inhabited by spirits who cannot be harmed with weapons!'\n\n";
    case 2:
        return "\nA shady character nods at you conspiratorially, 'The path through the Maw is beset with traps, ware you.'\n\n";
    case 3:
        return "\nA stout dwarf brags of his deeds, 'The goblins of Needletoe have wicked long claws. Best kept at arms length!'\n\n";
    case 4:
        return "\nA travelling scholar opines, 'It's said a fierce dragon lies beyond the Maw, its' scales impervious to simple weapons.\n\n";
    default:
        return "\nYou learn nothing of value.\n\n";
    }


}

//location reset function for game restart. Attempted to write with a list of locations and a for loop to reset each. Didn't work. One to figure out.

void reset_locs() {

    merchant.reset();
    tavern.reset();
    crossroads.reset();
    undercrypt.reset();
    needletoe_caverns.reset();
    maw_unknown.reset();
    maw_clear.reset();
    maw_trapped.reset();
    dragon_lair.reset();

    }


void play_game() {

    //sets out the initial instructions
    bool game_status = greeting();
    player.show_inv();

    //loops through the game choices until victory (or death!) condition  denoted by game_status==false
    while (game_status) {
        if (current_loc.is_clear()) {
            cout << "\nThis area is quiet and empty.\n\n";
            cout << "\nWith nothing left to do here, you return to The Crossroads.\n\n";
            current_loc = crossroads;
        }
        current_loc.locate();
        current_loc.describe();
        current_loc.show_options();
        game_status = choice();
    }
}

bool play_again() {

    string play_again;
    //determines if player wishes to play again
    cout << "\nWould you like to play again? Type Y for YES, any other key for NO\n\n";
    cin >> play_again;
    if (play_again == "y" || play_again == "Y") {
        current_loc = tavern;
        player.reset();
        reset_locs();
        return true;
    }
    else {

        return false;

    }
}

//core game data is contained in a series of switches, defined by the value of current_loc
bool choice() {

    string choose;
    cin >> choose;

    //Any text commands should be added before the try statement, which filters out any unknown strings.
    if (choose == "INV") {
        
        player.show_inv();
        return true;

    }
    else if (choose == "QUIT") {

        return false;

    }
    else {

        try {

            int val_test = stoi(choose);

        }

        catch (invalid_argument){

            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }

        catch (out_of_range) {

            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }
    }
    if (current_loc.get_name() == "The Thirsty Ferret") {
        switch (stoi(choose)) {
        case 1:
            cout << "\nYou tarry awhile and get blind drunk on the local grog.\n\n";
            return true;

        case 2:
            cout << get_rumour();
            return true;

        case 3:
            cout << "\nYou decide to visit the merchant.\n\n";
            current_loc = merchant;
            return true;

        case 4:
            cout << "\nYou set out into the wilds.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }
    }
    if (current_loc.get_name() == "Cloaks and Daggers") {
        switch (stoi(choose)) {

        case 1:
            player.buy_item("Thieves Tools", 1);
            return true;

        case 2:
            player.buy_item("Sword", 4);
            return true;

        case 3:
            cout << "\nYou visit the tavern.\n\n";
            current_loc = tavern;
            return true;

        case 4:
            cout << "\nYou set out into the wilds.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }

    }
    if (current_loc.get_name() == "Crossroads") {
        switch (stoi(choose)) {

        case 1:
            cout << "\nYou follow the overgrown path to the Undercrypt. A dark stoned tomb entrance looms before you.\n\n";
            current_loc = undercrypt;
            return true;

        case 2:
            cout << "\nYou take the steep, narrow mountainous trail to The Maw. A menacing cave entrance pierces the mists ahead.\n\n";
            if (maw_trapped.is_clear()) {
                current_loc = maw_clear;
            }
            else {
                current_loc = maw_unknown;
            }

            return true;

        case 3:
            cout << "\nA short distance from the crossroads, you encounter an abandoned mine entrance. Skeletons impaled with spears adorn either side.\n\n";
            current_loc = needletoe_caverns;
            return true;

        case 4:
            cout << "\nYou make your way back to the comfort of the Thirsty Ferret.\n\n";
            current_loc = tavern;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }
    }

    if (current_loc.get_name() == "Needletoe Caverns") {
        switch (stoi(choose)) {

        case 1:
            if (!player.check_inv("Sword")){
                cout << "\nWith no suitable weapon to fight off the goblins, you are quickly overwhelmed as they slash you to ribbons with their terrible claws.\n\n";
                cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
                return false;
            }

            else {

                cout << "\nYou cut through the goblins with your sword, keeping at arms length from their terrible talons.\n\n";
                cout << "As the dust of battle settles, you find a holy symbol attached to one of the goblins.\n";
                cout << "You put the Holy Symbol in your backpack and return to The Crossroads.\n\n";
                needletoe_caverns.clear();
                current_loc = crossroads;
                player.add_item("Holy Symbol");
                return true;
            }

        case 2:
            cout << "\nYou run away, back to the crossroads.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }

    }

    if (current_loc.get_name() == "Undercrypt") {
        switch (stoi(choose)) {

        case 1:
            if (player.check_inv("Sword") && !player.check_inv("Holy Symbol")) {
                cout << "\nYou swing at the spirit with your sword, but the blade passes through! The banshee grips you in a permanent, icy embrace.\n\n";
                cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
                return false;
            }

            else if (!player.check_inv("Holy Symbol")) {
                cout << "\nWith no suitable weapon to fight the spirit, you flail wildly at it. The banshee envelops you in an icy embrace.\n\n";
                cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
                return false;
            }

            else {

                cout << "\nYou draw your Holy Symbol from your backpack. The spirit shrieks in terror, then vanishes.\n\n";
                cout << "You discover an old lance amongst the debris of the crypt. It feels like an item of power.\n";
                cout << "You put the Dragon Lance in your backpack and return to The Crossroads.\n\n";
                undercrypt.clear();
                current_loc = crossroads;
                player.add_item("Dragon Lance");
                return true;
            }

        case 2:
            cout << "\nYou run away, back to the crossroads.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }

    }

    if (current_loc.get_name() == "Maw") {
        switch (stoi(choose)) {

        case 1:
            cout << "\nYou carelessly step toward the portal, oblivious to the disentegration field across your path, which reduces you to ash in an instant.\n\n";
            cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
            return false;

        case 2:
            cout << "\nYou carelessly step toward the portal, oblivious to the disentegration field across your path, which reduces you to ash in an instant.\n\n";
            cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
            return false;

        case 3:
            cout << "\nYour search identifies a device, which appears to generate a magical field across your path.\n\n";
            current_loc = maw_trapped;
            return true;

        case 4:
            cout << "\nYou run away, back to the crossroads.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }
    }

    if (current_loc.get_name() == "Maw Tunnel") {
        switch (stoi(choose)) {

        case 1:
            cout << "\nYou heedlessly step toward the portal, ignoring the disentegration field across your path, which reduces you to ash in an instant.\n\n";
            cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
            return false;

        case 2:
            cout << "\nYou heedlessly step toward the portal, ignoring the disentegration field across your path, which reduces you to ash in an instant.\n\n";
            cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
            return false;

        case 3:
            if (player.check_inv("Thieves Tools")) {
                cout << "\nBeads of sweat form on your brow as you carefully deactivate the device with your Thieves Tools.\n\n";
                cout << "\nThe magical field dissipates before you. Perhaps those piles of ash weren't as careful as you.\n\n";
                maw_trapped.clear();
                current_loc = maw_clear;
                return true;
            }
            else {
                cout << "\nYour clumsy efforts to deactivate the device without the proper tools fail catastrophically.\n";
                cout << "\nYou accidentally break the field with your hand, resulting in your disintegration.\n\n";
                cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
                return false;
            }

        case 4:
            cout << "\nYou run away, back to the crossroads.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }
    }

    if (current_loc.get_name() == "Maw Tunnel - Disintegration device deactivated!") {
        switch (stoi(choose)) {

        case 1:
            cout << "\nWith the trap disarmed, you step safely into the mystical portal.\n\n";
            current_loc = dragon_lair;
            return true;

        case 2:
            cout << "\nWith the trap disarmed, you step safely into the mystical portal.\n\n";
            current_loc = dragon_lair;
            return true;

        case 3:
            cout << "\nYou run away, back to the crossroads.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }
    }

    if (current_loc.get_name() == "Dragons' Lair") {
        switch (stoi(choose)) {

        case 1:
            if (player.check_inv("Sword") && !player.check_inv("Dragon Lance")) {
                cout << "\nYou valiantly charge towards the beast with your sword drawn, but you are unable to pierce the scaled hide with your blade.\n";
                cout << "\nThe wyrm covers you in a breath of molten flame, and you scream as your flesh melts and strips from your bones.\n\n";
                cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
                return false;
            }

            else if (!player.check_inv("Dragon Lance")) {
                cout << "\nWith no suitable weapon to fight the dragon, your efforts can only be described as suicidal.\n\n";
                cout << "\nThe wyrm covers you in a breath of molten flame, and you scream as your flesh melts and strips from your bones.\n\n";
                cout << "\nDarkness takes you. Perhaps you were not the Chosen One after all. Your quest is over.\n\n";
                return false;
            }

            else {

                cout << "\nYou draw your Dragon Lance and charge at the wyrm. The tip of the weapon catches the beast in the throat just as it prepares to engulf you in fiery doom.\n\n";
                cout << "The dragon chokes on its' own molten breath and collapses heavily to the floor\n";
                cout << "The riches of the dragons' hoard are yours to claim, adventurer! Congratulations, you have survived this adventure!\n\n";
                dragon_lair.clear();
                return false;
            }

        case 2:
            cout << "\nYou run away, back to the crossroads.\n\n";
            current_loc = crossroads;
            return true;

        default:
            cout << "\nInvalid choice. Try again.\n\n";
            return true;

        }

    }

}
