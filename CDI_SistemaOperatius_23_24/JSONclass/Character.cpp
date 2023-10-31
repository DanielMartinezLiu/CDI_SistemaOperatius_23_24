#include "Character.h"

Json::Value Character::Encode()
{
	Json::Value json;

	json["life"] = life;
	json["coin"] = coin;
	json["name"] = name;

	Json::Value weaponsArray = Json::Value(Json::arrayValue);

	for (Weapon* weapon : *weapons)
	{
		weaponsArray.append(weapon->Encode());
	}

	json["weapons"] = weaponsArray;

	return json;
}

Character* Character::Decode(Json::Value json)
{
	Character* character = new Character();

	character->life = json["life"].asInt();
	character->coin = json["coin"].asInt();
	character->name = json["name"].asString();

	Json::Value weaponsArray = json["weapons"];
	
	for (Json::Value weaponJson : weaponsArray)
	{
		Weapon* weapon = Weapon::Decode(weaponJson);
		character->weapons->push_back(weapon);
	}

	return character;
}