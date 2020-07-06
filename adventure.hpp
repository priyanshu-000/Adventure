//2020 MrN00b0t solution to Codecademy Build a Text Adventure Project
#include <iostream>
#include <string>
#include <vector>

class Player {

private:

	std::vector<std::string> inventory;
	std::vector<std::string> inv();
	std::string name;
	int gold;

public:


	Player(std::string new_name = "Bronan", std::vector<std::string> new_inventory = { "Backpack" }, int new_gold = 5);
	int gp();
	//displays inventory and gold
	void show_inv();
	//used for purchases
	void buy_item(std::string item, int cost);
	//checks inventory for a specific item
	bool check_inv(std::string item);
	//add item to inventory
	void add_item(std::string item);
	//reset inventory and gold
	void reset();

};

class Location {

private:

	std::string name;
	std::string description;
	std::vector<std::string> options;
	bool cleared = false;

public:
	
	Location(std::string new_name, std::vector<std::string> new_options, std::string new_description);

	void locate();
	void describe();
	void show_options();
	std::vector<std::string> get_options();
	std::string get_name();
	bool is_clear();
	void clear();
	void reset();

};

bool greeting();
void play_game();
bool choice();
std::string get_rumour();
bool play_again();
void reset_locs();

