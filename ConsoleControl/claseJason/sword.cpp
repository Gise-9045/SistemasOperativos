#include "sword.h"


Sword::Sword(std::string color) : color(color)
{
	damage = 2;
	type = SWORD;

	this->color = color;
};

Json::Value Sword::Encode()
{
	Json::Value json = Weapon::Encode(); 

	json["color"] = color; 

	return json;
}

Sword* Sword::Decode(Json::Value json)
{
	std::string color = json["color"].asString(); 
	Sword* sword = new Sword(color); 

	return sword;
}
