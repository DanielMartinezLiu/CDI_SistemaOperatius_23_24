#pragma once
#include <string>
#include "Weapon.h"

class Sword : public Weapon
{
public:
	std::string color = "";

	Sword(std::string color);

	Json::Value Encode();
	static Sword* Decode(Json::Value json);
};

