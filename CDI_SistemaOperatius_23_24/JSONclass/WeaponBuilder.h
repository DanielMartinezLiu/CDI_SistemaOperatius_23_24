#pragma once

#include "json/json.h"
#include "Weapon.h"

class WeaponBuilder
{
public:
	static Weapon* CreateWeaponFromJson(Json::Value json);
};