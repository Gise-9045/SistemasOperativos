#pragma once
#include "weapon.h"
#include <string>


class Sword : public Weapon
{
public: 
	std :: string color = "";

	Sword(std::string color);

	Json::Value Encode() override;
	static Sword* Decode(Json::Value json);

};


