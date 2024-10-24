#pragma once
#include <string>

using namespace std;

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
			Healing,
			Key,
			Equipment,
			Weapon,
		};

		//Constructors
		Item();
		Item(string n, string desc, Type t, int val);

		//Getters and setters
		string GetName();
		string GetDescription();
		Type GetType();
		int GetValue();
		void setName(string n);
		void setDescription(string desc);
		void setType(Type t);
		void setValue(int val);

	private:
		string name;
		string description;
		Type myType;
		int value;				//This value can be used to represent amount of HP healed, damage a weapon does, armor provided, etc... depending on the item Type.
	
};

