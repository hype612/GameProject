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
	heal = 0, mana, critStrike, critChance, dmgBoost, undefined
};
Consumable::Consumable() : name("undefined"), m_Type(effectType::undefined), scale(-1) {}
Consumable::Consumable(std::string consumableName, effectType type, float effectScale)
	: name(consumableName), m_Type(type), scale(effectScale) {}

Consumable::Consumable(std::string& statString)
{
	using namespace std;
	std::vector<std::string> stats = splitString(statString, ';');
	name = stats[0];
	char tempEffect = stats[1][1];
	m_Type = (effectType)tempEffect;
	scale = stof(stats[2]);
}




//
//========================
//	   Item
//========================
//
enum Item::itemType : int
{
	weapon , chest, hands, feet, head
};

Item::Item(std::string propName, double propValue, Item::itemType propType) : itemName(propName)
{
	//creating a new weapon
	if (propType == weapon)
	{
		armour = NULL;
		dmg = (int)propValue;
		type = Item::itemType::weapon;
	}
	//creating a new armor 
	else
	{
		dmg = NULL;
		switch (propType)
		{
		case Item::chest:
			type = Item::itemType::chest;
			break;

		case Item::hands:
			type = Item::itemType::hands;
			break;

		case Item::feet:
			type = Item::itemType::feet;
			break;

		case Item::head:
			type = Item::itemType::head;
			break;
		}
		armour = propValue;
	}
}

Item::Item(std::string& statString)
{
	using namespace std;
	std::vector<std::string> stats = splitString(statString, ';');
	itemName = stats[0];
	int tempType = std::stoi(stats[2]);
	//itemType tempTypetoItemType = (itemType)tempType;
	if (tempType == weapon)
	{
		armour = NULL;
		dmg = stoi(stats[1]);
		type = (Item::itemType)0;
	}
	else
	{
		dmg = NULL;
		switch (tempType)
		{
		case Item::chest:
			type = (Item::itemType)1;
			break;

		case Item::hands:
			type = (Item::itemType)2;
			break;

		case Item::feet:
			type = (Item::itemType)3;
			break;

		case Item::head:
			type = (Item::itemType)4;
			break;
		}
		armour = stof(stats[2]);
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
	//std::cout << "succesfully called getEDMG\n";
    if(equipment[0] != nullptr)
	    return -(baseDmg * equipment[0]->dmg);
    else
        return baseDmg;
	//make weapon dmg 1 default B4
	//return 0;
}



void Player::dMove(char direction, std::array<int, 2>& oArray)
{
    oArray[0] = roomPos[0];
    oArray[1] = roomPos[1];
    switch(direction)
    {
        case 'w':
            roomPos[0]--;
            break;
        case 'a':
            roomPos[1]--;
            break;
        case 's':
            roomPos[0]++;
            break;
        case 'd':
            roomPos[1]++;
            break;
        default:
            std::cout << "wrong character: not a direction\n";
    }
}



bool Player::equip(Item& item)
{
    std::cout << (char)item.type << std::endl;
	if (equipment[item.type] == nullptr)
	{
		equipment[item.type] = &item;
        return true;
	}
	else
	{
		std::cout <<"You already have an item equipped on that slot.\nComparing the stats:...\n";
		std::cout <<"Name:	" << equipment[item.type]->itemName << "	" << item.itemName << "\n";
		if (item.type > 0)
			std::cout << "Armor rating:	" << equipment[item.type]->armour << "		" << item.armour << "\n";
		else
			std::cout <<"Damage: " << -1 * equipment[item.type]->dmg << "		" << -1 * item.dmg << "\n";


		std::cout << "Do you want to switch? (y/n): ";
		char takeinvar;
		std::cin >> takeinvar;
		if (takeinvar == 'y')
		{
			equipment[item.type] = &item;
			std::cout << "Switched your item\n";
            return true;
		}
		else
		{
			std::cout << "Keeping your original item\n";
            return false;
		}
	}
}


void Player::addConsumable(std::string initName, Consumable::effectType initType, float initScale)
{
	inventory.emplace_back(initName, initType, initScale);
}



void Player::useConsumable(int id)
{
    if(inventory[id].scale == 0.0f)
        std::cout << "there's no consumable on that slot!\n";
    else
    {
       switch(inventory[id].m_Type)
       {
           case Consumable::effectType::heal:
               entityHP += inventory[id].scale;
               break;
           case Consumable::effectType::mana:
               entityMana += inventory[id].scale;
               break;
        //others not yet added
       }
       removeConsumable(inventory[id]);
    }
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

int Player::spellCast(int spellNum)
{
	if (entityMana + 1 > spellbook[spellNum].getCost())
	{
		entityMana -= spellbook[spellNum].getCost();
		return spellbook[spellNum].getAmount();
	}
	else
	{
		std::cout << "NOT ENOUGH MANA!\n";
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
