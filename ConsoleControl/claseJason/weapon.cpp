#include "weapon.h"
#include "sword.h"
#include "lance.h"

Json::Value Weapon::Encode()
{
	return Json::Value();
}

Weapon* Weapon::Decode(Json::Value json)
{
	WeaponType  type = (WeaponType)json["type"].asInt(); 

	Weapon* weapon = nullptr; 

	switch (type)
	{
	case Weapon::UNKNOWN:
		return nullptr; 
		break;
	case Weapon::SWORD:
		weapon = Sword::Decode(json); 
		break;
	case Weapon::LANCE:
		weapon = Lance::Decode(json); 
		break;
	default:
		return nullptr; 
		break;
	}

	weapon->type = type; 


	weapon->damage = json["damage"].asInt(); 
	weapon->range = json["range	"].asInt(); 


	return weapon;
}
