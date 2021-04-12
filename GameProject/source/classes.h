#pragma once

#include "main.h"



//23.03.2021
//As of now There's a constructor implemented for every class
//that takes a string as an argument. Later on find a way
//to merge this into one function/method



class Spell
{
private:
	std::string spellID;
	int amount;
	int manacost;
	std::string description;
public:
	Spell();
	Spell(std::string name, int size, int cost, std::string desc);
	Spell(std::string& statString);

	std::string getSpellId();
	int getAmount();
	int getCost();
	std::string getDesc();
	
	void getSpell();
};

struct Consumable
{
public:
	enum class effectType : char;
	std::string name;
	effectType m_Type;
	float scale;

	Consumable();
	Consumable(std::string consumableName, effectType type, float effectScale);
	Consumable(std::string& statString);

};

struct Item
{
public:
	enum itemType : int;
	std::string itemName;
	itemType type;
	int dmg;
	double armour;

	Item(std::string propName, double propValue, Item::itemType propType);
	Item(std::string& statString);
};



class Entity
{
public:
	std::string entityName;
	int entityHP, entityMana;
	float multiplier;
public:
	Entity() : entityName("undefined"), entityHP(-1), entityMana(-1), multiplier(0.0f), baseDmg(-1) {}

	Entity(std::string initName, int initHP, int initMana, float initMulti, int initDmg)
		: entityName(initName), entityHP(initHP), baseDmg(initDmg), entityMana(initMana), multiplier(initMulti) {}

	virtual int getEntityDmg();

protected:
	int baseDmg;
};

class Player : public Entity
{
public:

    //basic variables of player
	std::vector<Consumable> inventory;
	std::array<Item*, 5> equipment = {nullptr};
	std::array<Spell, 2> spellbook { Spell("Fireball", -50, 10, "Do you like to play with fire??"), Spell("Tome of Healing", 30, 20, "A mediocre healing spell for those who are not familiar with the way of magic") };
	size_t dungeonPos, globalPos;
    int roomPos[2] = {0, 0};

    //constructor(s) and inherited functions
	Player(std::string initName, int initHP, int initMana, float initMulti, int initDmg);
	int getEntityDmg() override;


    //basic functions of the player
    void dMove(char direction, std::array<int, 2>& oArray);


    //item related
	bool equip(Item& item);



    //consumable related
	void addConsumable(std::string initName, Consumable::effectType initType, float initScale);
	void removeConsumable(Consumable& consumable);
    void useConsumable(int id); 



    //spell related
	int spellCast(int spellNum);
	//void enterDungeon();
};


class Enemy : public Entity
{
public:
	Enemy(std::string name, int hp, int mana, float multi, int dmg);
	Enemy(std::string& statString);
};
