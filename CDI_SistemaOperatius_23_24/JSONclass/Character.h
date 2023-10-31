#pragma once
#include <string>
#include <json/json.h>
#include <vector>

#include "Weapon.h"

class Character
{
public:
	int life = 0;
	int coin = 0;
	std::string name = "";
	std::vector<Weapon*>* weapons = new std::vector<Weapon*>();


	Json::Value Encode();
	static Character* Decode(Json::Value json);
};