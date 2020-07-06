//2020 MrN00b0t solution to Codecademy Build a Text Adventure Project
#include <iostream>
#include <string>
#include <vector>
#include "adventure.hpp"

int main (){

bool game_status = true;

while (game_status) {

	play_game();
	game_status = play_again();

}  
}