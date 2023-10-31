#pragma once
#include <string>
#include "weapon.h"

class Lance : public Weapon
{
public: 
	std::string woodType = ""; 

	Lance(std::string woodType);

	Json::Value Encode() override;
	static Lance* Decode(Json::Value json);

};

