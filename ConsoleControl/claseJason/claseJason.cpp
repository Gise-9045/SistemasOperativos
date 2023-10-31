// claseJason.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <json/json.h>
#include "Character.h"
#include <fstream>
#include "sword.h"
#include "lance.h"


void CreateBaseCharacter(); 
void ReadBaseCharacter(); 

int main()
{
    std::cout << "Hello World!\n";
    CreateBaseCharacter(); 
    //ReadBaseCharacter(); 
}

void CreateBaseCharacter()
{
    Character* character = new Character();

    character->life = 5; 
    character->coin = 5; 
    character->name = "UWU hero"; 

    Sword* _sword = new Sword("Plateada");
    Lance* _lance = new Lance("Pino"); 

    character->weapons->push_back(_sword); 
    character->weapons->push_back(_lance); 
    character->weapons->push_back(_sword); 


    Json::Value json; 
    //json["life"] = character->life; 
    //json["coin"] = character->coin; 
    //json["name"] = character->name; 

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
    Character* character = new Character(); 

    std::ifstream jsonReadFile = std::ifstream("Character.json", std::ifstream::binary); 

    if (!jsonReadFile.fail())
    {
        Json::Value json; 
        jsonReadFile >> json; 
        jsonReadFile.close();

        Character* character = Character::Decode(json["Character"]);

        int i = 0; 
    }
}

