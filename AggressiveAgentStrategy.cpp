//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2016

#include <vector>
#include"Game.h"
#include "Strategy.h"
#include "Gaming.h"
#include "AggressiveAgentStrategy.h"

namespace Gaming
{
	const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

	AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
	{
		__agentEnergy = agentEnergy;
	}

	AggressiveAgentStrategy::~AggressiveAgentStrategy()
	{

	}

	ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const
	{
		Position moveTo;
		PositionRandomizer randomTarget;
		std::vector<int> agent, advant, food, empty;

		// record the surroundings, excluding itself
		for (int i = 0; i < 9; i++)
		{
			if (s.array[i] == 0 || s.array[i] == 1)
				agent.push_back(i);

			else if (s.array[i] == 3)
				advant.push_back(i);

			else if (s.array[i] == 2)
				food.push_back(i);

			else if (s.array[i] == 6)
				empty.push_back(i);

			if (i == 3)  //This is where the agent is
				i++;
		}


		// determine the course of action
		if (!agent.empty() && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)  
			moveTo = randomTarget(agent);

		else if (!advant.empty())
			moveTo = randomTarget(advant);

		else if (!food.empty())
			moveTo = randomTarget(food);

		else if (!empty.empty())
			moveTo = randomTarget(empty);

		else
			return STAY;



		// return the direction based on PositionRandomizer position
		switch (moveTo.x)
		{
		case 0:
		{
			switch (moveTo.y)
			{
			case 0: return NE;
			case 1: return N;
			case 2: return NW;
			}
		}
		case 1:
		{
			switch (moveTo.y)
			{
			case 0: return E;
			case 1: return STAY;
			case 2: return W;
			}
		}
		case 2:
		{
			switch (moveTo.y)
			{
			case 0: return SE;
			case 1: return S;
			case 2: return SW;
			}
		}
		}
		return STAY;
	}
}

