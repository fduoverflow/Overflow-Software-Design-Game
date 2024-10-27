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
    if (isEmpty) {
        cout << "Your inventory is empty!" << endl;
    }
    else {
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
        }
    }
}

void Inventory::addItem(Item& item) {
    for (int i = 0; i < size; i++) {
        if (contents[i].GetType() == Item::Type::EMPTY) {
            contents[i] = item;
            cout << "Added item: " << item.GetName() << endl;
            break;
        }
    }
    if (isEmpty) {
        isEmpty = false;
    }
    if (contents[size-1].GetType() != Item::Type::EMPTY) {
        cout << "Inventory is full. Could not add item: " << item.GetName() << endl;
    }
    return;
}