#include "Inventory.h"
#include <iostream>

using namespace std;

Inventory::Inventory() {
    size = 0;
    contents = new Item[0];
}

Inventory::Inventory(int s) {
    size = s;
    contents = new Item[s];
}

void Inventory::displayInventory() {
    cout << "Inventory:" << endl;
    for (int i = 0; i < size; i++) {
        if (contents[i].GetType() != Item::Type::EMPTY) {                   // Display items.
            cout << "Name: " << contents[i].GetName() << endl;
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
        }
        else if(contents[i].GetType() == Item::Type::EMPTY) {                   //Display that the inventory is empty.
            cout << "Inventory is empty." << endl;
            break;
        }
    }
 }