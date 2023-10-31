#include "Character.h"
#include "WeaponBuilder.h"

Json::Value Character::Encode()
{
	//crear un json apartir del objeto que esta creado

	Json::Value json; 

	json["life"] = life; 
	json["coin"] = coin; 
	json["name"] = name; 

	//AÑADIR UN VECTOR 
	Json::Value weaponsArray = Json::Value(Json::arrayValue); 

	for (Weapon* weapon : *weapons)
	{
		weaponsArray.append(weapon->Encode()); 
	}
	json["weapons"] = weapons; 

	return json; 
}

Character* Character::Decode(Json::Value json)
{
	Character* character = new Character(); 
	character->life = json["life"].asInt();
	character->coin = json["coin"].asInt();
	character->name = json["name"].asString(); 

	Json::Value weaponsArray = json["weapons"]; 
	for (Json::Value weaponsJson : weaponsArray)
	{
		Weapon* weapon = WeaponBuilder::CreateWeaponFromJson(weaponsJson);
		character->weapons->push_back(weapon);
	}

	return character;
}
