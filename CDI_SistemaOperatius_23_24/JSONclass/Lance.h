#pragma once
#include <string>
#include "Weapon.h"

class Lance : public Weapon
{
public:
	std::string woodType = "";

	Lance(std::string woodType);

	Json::Value Encode();
	static Lance* Decode(Json::Value json);
};

