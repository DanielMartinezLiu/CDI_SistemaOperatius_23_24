#include <iostream>
#include <json/json.h>
#include <fstream>

#include "Character.h"
#include "Sword.h"
#include "Lance.h"

void CreateBaseCharacter();
void ReadBaseCharacter();

int main()
{
	CreateBaseCharacter();
	//ReadBaseCharacter();

	std::cout << "\nHello World" << std::endl;
}

void CreateBaseCharacter()
{
	Character* character = new Character();

	character->life = 10;
	character->coin = 0;
	character->name = "Aaron Deza";

	Sword* sword = new Sword("Plateada");
	Lance* lance1 = new Lance("Roble");
	Lance* lance2 = new Lance("Pino");

	character->weapons->push_back(sword);
	character->weapons->push_back(lance1);
	character->weapons->push_back(lance2);

	Json::Value json;
	/*
	json["life"] = character->life;
	json["coin"] = character->coin;
	json["name"] = character->name;
	*/
	json["Character"] = character->Encode();

	std::ofstream jsonWriteFile = std::ofstream("Character.json", std::ofstream::binary);

	if (!jsonWriteFile.fail())
	{
		jsonWriteFile << json;
		jsonWriteFile.close();
	}
}

void ReadBaseCharacter()
{
	Character c;

	c.name = "Hola;";

	Character* character = new Character(c);

	std::ifstream jsonReadFile = std::ifstream("Character.json", std::ifstream::binary);

	if (!jsonReadFile.fail())
	{
		Json::Value json;
		jsonReadFile >> json;
		jsonReadFile.close();

		/*
		character->life = json["life"].asInt();
		character->coin = json["coin"].asInt();
		character->name = json["name"].asString();
		*/

		Character* character = Character::Decode(json["Character"]);

		std::cout << "Life: " << character->life << "\nCoin: " << character->coin << "\nName: " << character->name;

	}
}