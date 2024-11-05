#include "Inventory.h"
#include <iostream>

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
                cout << "\nName: " << contents[i].GetName() << endl;
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