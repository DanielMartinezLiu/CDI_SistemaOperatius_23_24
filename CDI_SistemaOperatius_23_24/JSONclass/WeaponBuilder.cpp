#include "WeaponBuilder.h"
#include "Sword.h"
#include "Lance.h"

Weapon* WeaponBuilder::CreateWeaponFromJson(Json::Value json)
{
    Weapon::WeaponType type = (Weapon::WeaponType)json["type"].asInt();

    Weapon* weapon = nullptr;

    switch (type)
    {
    case Weapon::UNKNOWN:
        return nullptr;
    case Weapon::SWORD:
        weapon = Sword::Decode(json);
        break;
    case Weapon::LANCE:
        weapon = Lance::Decode(json);
        break;
    default:
        return nullptr;
    }

    weapon->type = type;

    weapon->damage = json["damage"].asInt();
    weapon->range = json["range"].asInt();

    return weapon;
}