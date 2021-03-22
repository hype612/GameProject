#include "classes.h"
#include "init.h"


//
//========================
//	    Spell
//========================
//
Spell::Spell()
	: spellID("Unknown spell"), amount(0), manacost(0), description("NO SPELL DECLARED") {}

Spell::Spell(std::string name, int size, int cost, std::string desc)
	: spellID(name), amount(size), manacost(cost), description(desc)
{
	//Log("Created Spell with prefixed stats!");
}

std::string Spell::getSpellId() { return spellID; }
int Spell::getAmount() { return amount; }
int Spell::getCost() { return manacost; }
std::string Spell::getDesc() { return description; }

void Spell::getSpell()
{
	std::cout << "\nListing spell details...\n";
	std::cout << "Name: " << getSpellId() << "\nHP modified: " << getAmount() << "\nCost: " << getCost() << "\n" << getDesc() << "\n";
}


//
//========================
//	Consumable
//========================
//
enum class Consumable::effectType : char
{
	heal = 0, speedBoost, critStrike, critChance, dmgBoost, undefined
};
Consumable::Consumable() : name("undefined"), m_Type(effectType::undefined), scale(-1) {}
Consumable::Consumable(std::string consumableName, effectType type, float effectScale)
	: name(consumableName), m_Type(type), scale(effectScale) {}



//
//========================
//	   Item
//========================
//
enum Item::itemType : char
{
	weapon = 0, chest, hands, feet, head
};

Item::Item(std::string propName, double propValue, Item::itemType propType) : itemName(propName)
{
	//creating a new weapon
	if (propType == weapon)
	{
		armour = NULL;
		dmg = (int)propValue;
		type = weapon;
	}
	//creating a new armor 
	else
	{
		dmg = NULL;
		switch (propType)
		{
		case Item::chest:
			type = chest;
			break;

		case Item::hands:
			type = hands;
			break;

		case Item::feet:
			type = feet;
			break;

		case Item::head:
			type = head;
			break;
		}
		armour = propValue;
	}
}




//
//========================
//	   Entity
//========================
//
int Entity::getEntityDmg()
{
	return baseDmg;
}


//
//========================
//	   Player
//========================
//
Player::Player(std::string initName, int initHP, int initMana, float initMulti, int initDmg)
	: Entity(initName, initHP, initMana, initMulti, initDmg)
{
	inventory.reserve(10);
	dungeonPos = -1;
	globalPos = 0; 
}

int Player::getEntityDmg()
{
	std::cout << "succesfully called getEDMG\n";
	//return basedmg * weapon dmg
	//make weapon dmg 1 default B4
	return 0;
}

void Player::equip(Item& item)
{
	if (equipment[item.type] == nullptr)
	{
		equipment[item.type] = &item;
	}
	else
	{
		std::cout <<"You already have an item equipped on that slot.\nComparing the stats:...\n";
		std::cout <<"Name:	" << equipment[item.type]->itemName << "	" << item.itemName << "\n";
		if (item.type > 0)
			std::cout << "Armor rating:	" << equipment[item.type]->armour << "		" << item.armour << "\n";
		else
			std::cout <<"Damage: " << -1 * equipment[item.type]->dmg << "		" << -1 * item.dmg << "\n";


		std::cout << "Do you want to switch? (y/n)\n";
		char takeinvar;
		std::cin >> takeinvar;
		if (takeinvar == 'y')
		{
			equipment[item.type] = &item;
			std::cout << "Switched your item\n";
		}
		else
		{
			std::cout << "Keeping your original item\n";
		}
	}
}


void Player::addConsumable(std::string initName, Consumable::effectType initType, float initScale)
{
	inventory.emplace_back(initName, initType, initScale);
}


void Player::removeConsumable(Consumable& consumable)
{
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (consumable.name == inventory[i].name)
		{
			inventory.erase(inventory.begin() + i);
			break;
		}
	}
}

//int???
int Player::spellCast(int spellNum)
{
	if (entityMana + 1 > spellbook[spellNum].getCost())
	{
		entityMana -= spellbook[spellNum].getCost();
		return spellbook[spellNum].getAmount();
	}
	else
	{
		std::cout << "Not Enough Mana!\n";
		return 0;
	}
}

//
//========================
//	    Enemy
//========================
//
Enemy::Enemy(std::string name, int hp, int mana, float multi, int dmg)
	: Entity(name, hp, mana, multi, dmg) {}



Enemy::Enemy(std::string& statString)
{
	using namespace std;
	std::vector<std::string> stats = splitString(statString, ';');
	entityName = stats[0];
	entityHP = stoi(stats[1]);
	entityMana = stoi(stats[2]);
	multiplier = stoi(stats[3]);
	baseDmg = stoi(stats[4]);
}

