//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2016

#include<iomanip>
#include"Game.h"
#include"Agent.h"
#include"Simple.h"

namespace Gaming
{
	const char Simple::SIMPLE_ID = 'S';

	Simple::Simple(const Game & g, const Position & p, double energy) : Agent(g, p, energy)
	{
	}

	Simple::~Simple()
	{
	}

	void Simple::print(std::ostream & os) const
	{
		os << this->SIMPLE_ID << std::left << std::setw(4) << this->__id;
		os << std::setw(0);
	}

	ActionType Simple::takeTurn(const Surroundings & s) const
	{
		std::vector<int> resources, empty;

		Position pos(1, 1);

		for (int count = 0; count < s.array.size(); ++count) 
		{
			if (s.array[count] == FOOD || s.array[count] == ADVANTAGE)
				resources.push_back(count);
			else if (s.array[count] == EMPTY)
				empty.push_back(count);
		}

		if (resources.size() > 0)
			return __game.reachSurroundings(pos, Game::randomPosition(resources));
		else if (empty.size() > 0)
			return __game.reachSurroundings(pos, Game::randomPosition(empty));
		else
			return STAY;
	}
}