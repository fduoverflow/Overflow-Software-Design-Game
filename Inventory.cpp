#include "Inventory.h"
#include <iostream>
#include <algorithm>

using namespace std;

Inventory::Inventory() {
    size = 25;
    contents = new Item[25];
    isEmpty = true;
}

Inventory::Inventory(int s) {
    size = s;
    contents = new Item[s];
    isEmpty = true;
}

void Inventory::displayInventory() {
    cout << "Inventory:" << endl;
    if (isEmpty) {                                          //Checks to see if inventory is empty
        cout << "Your inventory is empty!" << endl;
    }
    else {
        for (int i = 0; i < size; i++) {
            if (contents[i].GetType() != Item::Type::EMPTY) {                   // Display items
                cout << "\nName: " << contents[i].GetName();
                if (contents[i].IsCurrentlyEquipped())
                    cout << " (Equipped)" << endl;
                else
                    cout << "\n";
                cout << "Description: " << contents[i].GetDescription() << endl;
                cout << "Type: ";
                // Display the type of the item
                switch (contents[i].GetType()) {
                case Item::Type::HEALING: cout << "Healing";
                    break;
                case Item::Type::KEY: cout << "Key";
                    break;
                case Item::Type::EQUIPMENT: cout << "Equipment";
                    break;
                case Item::Type::WEAPON: cout << "Weapon";
                    break;
                }
                cout << "\nValue: " << contents[i].GetValue() << endl;
                cout << "Quantity: " << contents[i].GetQuantity() << endl;
            }
        }
    }
}

void Inventory::addItem(Item& item) {   
    // Adds items if duplicated by changing quantity
    for (int i = 0; i < size; i++) {
        if (contents[i].GetType() == item.GetType() && contents[i].GetName() == item.GetName()) {
            contents[i].setQuantity(contents[i].GetQuantity()+1); // Increase quantity if duplicate
            cout << "Increased quantity of: " << item.GetName() << " to " << contents[i].GetQuantity() << endl;
            return;
        }
    }
    // Adds items if not duplicated
    for (int i = 0; i < size; i++) {
        if (contents[i].GetType() == Item::Type::EMPTY) {
            contents[i] = item;
            contents[i].setQuantity(1);
            cout << "Added item: " << item.GetName() << endl;
            break;
        }
    }
    if (isEmpty) {                                      // Changes the isEmpty to false since there are items in there
        isEmpty = false;
    }
    if (contents[size-1].GetType() != Item::Type::EMPTY) {                              // Checks to see if the inventory is full
        cout << "Inventory is full. Could not add item: " << item.GetName() << endl;
    }
    return;
}

/*
* Remove Item from Inventory using its name as a passed string parameter.
* The passed string must already be normalized.
* Calling this method assumes the inventory is not empty since the method must return an Item object.
* Method will return an empty Item object if these requirements are not met.
*/
Item Inventory::removeItem(string itemName)
{
    //Initialize temp control variables
    string currentInvItemName;
    Item itemCopy = Item();

    //Check for Item then remove it.
    for (int i = 0; i < size; i++)
    {
        //Grab item name from array and normalize it to match passed normalized string parameter.
        currentInvItemName = contents[i].GetName();
        transform(currentInvItemName.begin(), currentInvItemName.end(), currentInvItemName.begin(), ::toupper);

        //Check if Item is found
        if (currentInvItemName == itemName)
        {
            //Grab found Item
            itemCopy = contents[i];

            //Decrement quantity by 1 or replace with empty Item object if quantity is 1 or less.
            if (contents[i].GetQuantity() <= 1)
                contents[i] = Item();
            else
                contents[i].setQuantity(contents[i].GetQuantity() - 1);
        }
    }

    //Update isEmpty
    isEmpty = true;
    for (int i = 0; i < size; i++)
    {
        if (contents[i].GetType() != Item::Type::EMPTY)
            isEmpty = false;
    }

    //Return found Item or empty Item if no match found in Inventory.
    return itemCopy;
}

/*
* Look for an Item in Inventory and return its reference.
* Assumes passed string is normalized.
* Will return nullptr if search did not find the item.
*/
Item* Inventory::findItem(string itemName)
{
    //Initialize temp control variables
    string currentInvItemName;

    for (int i = 0; i < size; i++)
    {
        //Noralize name to match passed string
        currentInvItemName = contents[i].GetName();
        transform(currentInvItemName.begin(), currentInvItemName.end(), currentInvItemName.begin(), ::toupper);

        if (currentInvItemName == itemName)
            return &contents[i];
    }

    //Return empty first item in inventory on failed search
    return nullptr;
}