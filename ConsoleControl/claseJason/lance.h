#pragma once
#include <string>
#include "weapon.h"

class Lance : public Weapon
{
public: 
	std::string woodType = ""; 

	Lance(std::string woodType) : woodType(woodType) 
	{ 
		range = 2; type = LANCE;  
	};

	Json::Value Encode();
	static Lance* Decode(Json::Value json);

};

