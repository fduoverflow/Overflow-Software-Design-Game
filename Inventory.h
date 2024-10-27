#pragma once
#include "Item.h"

static class Inventory{
private:
	int size;			// The number of different items the inventory can hold (note: need to refector if we want a flexible inventory)
	Item* contents;	// A dynamically allocated array of the items that are being stored
public:
	Inventory();		// Default constructor
	Inventory(int s);		// Constructor that takes in the size of the inventory
	void displayInventory(); // Displays the inventory
};