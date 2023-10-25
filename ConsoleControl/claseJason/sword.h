#pragma once
#include "weapon.h"
#include <string>


class Sword : public Weapon
{
public: 
	std :: string color = "";

	Sword(std::string color) : color(color) 
	{
		damage = 2; type = SWORD;
	};

	Json::Value Encode();
	static Sword* Decode(Json::Value json);

};


