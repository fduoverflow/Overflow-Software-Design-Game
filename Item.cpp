#include "Item.h"

using namespace std;

//Constructors
Item::Item()
{
	name = "";
	description = "";
	myType = Type::EMPTY;
	value = 0;
}
Item::Item(string n, icon i, string desc, Type t, int val)
{
	name = n;
	myIcon = i;
	description = desc;
	myType = t;
	value = val;
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