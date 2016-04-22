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
		os << SIMPLE_ID << std::left << std::setw(4) << __id << std::setw(0);
	}

	ActionType Simple::takeTurn(const Surroundings & s) const
	{
		std::vector<int> resources, empties;
		Position curr(1, 1);

		for (int pos = 0; pos < 9; ++pos)
		{
			if (s.array[pos] == FOOD || s.array[pos] == ADVANTAGE)
				resources.push_back(pos);
			else if (s.array[pos] == EMPTY)
				empties.push_back(pos);
		}

		if (resources.size())
			return __game.reachSurroundings(curr, Game::randomPosition(resources));

		else if (empties.size())
			return __game.reachSurroundings(curr, Game::randomPosition(empties));

		else
			return STAY;
	}
}