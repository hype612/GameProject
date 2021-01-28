#include "events.h"

namespace entityEvent {
	void changeHealth(int amount, Entity& entity)
	{
		entity.entityHP += amount;
	}

	
}

namespace WorldEvent {
	void Fight(Player& player, Entity& enemy)
	{
		char action;
		int i = 0;
		int& f1Hp = player.entityHP;
		int& f2Hp = enemy.entityHP;

		do
		{
			i++;
			std::cout << "round " << i << "\n";
			std::cout << "Your HP: " << f1Hp << " Troll's HP: " << f2Hp << "\n";
			std::cout << "_______________________________________\n";
			std::cout << "What will you do?\n";
			std::cout << "Basic attack - Q	Fireball(10) - W	Tome of Healing(20) - E\n";
			std::cin >> action;
			switch (action)
			{
			case 'q':
				//f2Hp -= player->basicAttack();
				entityEvent::changeHealth(player.getEntityDmg(), enemy);
				std::cout << " \n";
				continue;
			case 'w':
				entityEvent::changeHealth(player.spellCast(0), enemy);
				std::cout << " \n";
				continue;
			case 'e':
				entityEvent::changeHealth(player.spellCast(1), player);
				std::cout << " \n";
				continue;
			}
		} while (f1Hp > 0 && f2Hp > 0);

		if (f1Hp > f2Hp)
			std::cout << "You won the fight!\n";
		else
			std::cout << "You lost\n";

	}
}
