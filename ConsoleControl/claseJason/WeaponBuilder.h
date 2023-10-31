#pragma once
#include <json/json.h>
#include "weapon.h"
#include "sword.h"
#include "lance.h"

class WeaponBuilder
{
public: 
	static Weapon* CreateWeaponFromJson(Json::Value json); 
};

