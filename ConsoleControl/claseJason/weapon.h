#pragma once
#include <json/json.h>

class	Weapon
{
public:
	enum WeaponType
	{
		UNKNOWN = 0, SWORD = 1, LANCE = 2
	};

	int damage = 1;
	int range = 1;

	WeaponType type = UNKNOWN; 

	Json::Value Encode();
	static Weapon* Decode(Json::Value json);

};

