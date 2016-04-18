//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2016

#include<iomanip>
#include"Game.h"
#include"Agent.h"
#include"Strategy.h"
#include"Strategic.h"
#include"DefaultAgentStrategy.h"

namespace Gaming
{
	const char Strategic::STRATEGIC_ID = 'T';

	Strategic::Strategic(const Game & g, const Position & p, double energy, Strategy * s) : Agent(g, p, energy)
	{
		__strategy = s;
	}

	Strategic::~Strategic()
	{
	}

	void Strategic::print(std::ostream & os) const
	{
		os << STRATEGIC_ID << std::left << std::setw(4) << __id;
		os << std::setw(0);
	}

	ActionType Strategic::takeTurn(const Surroundings & s) const
	{
		return (*__strategy)(s);
	}
}