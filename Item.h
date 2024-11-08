#pragma once
#include <string>

using namespace std;

// Structure for visualizing objects and characters
// Where to place this so its universal?
struct icon {
	wstring emoji;
	int size;
};

/*
* Item class represents items that the Player can use.
* Each item will have a name, description, and type.
* Healing items will restore the player's HP
* Key items can be used in certain situations such as a quest or puzzle.
* Equipment can be put on by the player to alter their stats.
* Weapons will affect how the player can attack.
*/
class Item
{
	public:
		//Item types
		enum class Type
		{
			HEALING,
			KEY,
			EQUIPMENT,
			WEAPON,

			EMPTY		//Default type for empty item objects if the default constructor is called. Avoid using unless you need an empty item object.
		};

		//Constructors
		Item();
		Item(string n, icon i, string desc, Type t, int val);

		//Getters and setters
		string GetName();
		string GetDescription();
		Type GetType();
		int GetValue();
		icon GetIcon();
		void setName(string n);
		void setDescription(string desc);
		void setType(Type t);
		void setValue(int val);

	private:
		string name;
		string description;
		Type myType;
		int value;				//This value can be used to represent amount of HP healed, damage a weapon does, armor provided, etc... depending on the item Type.
		icon myIcon;
};

