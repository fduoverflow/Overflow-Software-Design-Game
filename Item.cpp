#include "Item.h"

using namespace std;

/*
* Default constructor
*/
Item::Item()
{
	name = "";
	description = "";
	myType = Type::EMPTY;
	value = 0;
	quantity = 0;
	isEquipped = false;
}

/*
* Item constructor that takes in a name, icon, description, type, value, and quantity
*/
Item::Item(string n, icon i, string desc, Type t, int val, int q)
{
	name = n;
	myIcon = i;
	description = desc;
	myType = t;
	value = val;
	quantity = q;
	isEquipped = false;
}

//Getters and setters
string Item::GetName()
{
	return name;
}
icon Item::GetIcon() {
	return myIcon;
}
string Item::GetDescription()
{
	return description;
}
Item::Type Item::GetType()
{
	return myType;
}
int Item::GetValue()
{
	return value;
}
int Item::GetQuantity()
{
	return quantity;
}
bool Item::IsCurrentlyEquipped()
{
	return isEquipped;
}
void Item::setName(string n)
{
	name = n;
}
void Item::setDescription(string desc)
{
	description = desc;
}
void Item::setType(Type t)
{
	myType = t;
}
void Item::setValue(int val)
{
	value = val;
}
void Item::setQuantity(int q)
{
	quantity = q;
}
void Item::Equip()
{
	isEquipped = !isEquipped;
}