#pragma once
#include "Item.h"

static class Inventory {
private:
	int size;			// The number of different items the inventory can hold (note: need to refector if we want a flexible inventory)
	Item* contents;	// A dynamically allocated array of the items that are being stored
	bool isEmpty;   // Checks to see if inventory is empty
public:
	Inventory();		// Default constructor
	Inventory(int s);		// Constructor that takes in the size of the inventory
	void displayInventory(); // Displays the inventory
	void addItem(Item& item); //Adds item to inventory
	Item removeItem(string itemName); //Removes item to inventory
	Item* findItem(string itemName); //Find and return reference to item to inventory

	// Public getter for isEmpty
	bool IsEmpty() const { return isEmpty; }
};