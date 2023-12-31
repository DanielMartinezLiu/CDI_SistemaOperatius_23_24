#include "Lance.h"

Lance::Lance(std::string woodType)
{
	type = LANCE;

	range = 2;
	this->woodType = woodType;
}
Json::Value Lance::Encode()
{
	Json::Value json = Weapon::Encode();

	json["woodType"] = woodType;

	return json;
}
Lance* Lance::Decode(Json::Value json)
{
	std::string woodType = json["woodType"].asString();

	Lance* lance = new Lance(woodType);

	return nullptr;
}