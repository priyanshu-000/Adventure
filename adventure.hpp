//2020 MrN00b0t solution to Codecademy Build a Text Adventure Project
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {

private:

	vector<string> inventory;
	vector<string> inv();
	string name;
	int gold;

public:


	Player(string new_name = "Bronan", vector<string> new_inventory = { "Backpack" }, int new_gold = 5);
	int gp();
	//displays inventory and gold
	void show_inv();
	//used for purchases
	void buy_item(string item, int cost);
	//checks inventory for a specific item
	bool check_inv(string item);
	//add item to inventory
	void add_item(string item);
	//reset inventory and gold
	void reset();

};

class Location {

private:

	string name;
	string description;
	vector<string> options;
	bool cleared = false;

public:
	
	Location(string new_name, vector<string> new_options, string new_description);

	void locate();
	void describe();
	void show_options();
	vector<string> get_options();
	string get_name();
	bool is_clear();
	void clear();
	void reset();

};

bool greeting();
void play_game();
bool choice();
string get_rumour();
bool play_again();
void reset_locs();

