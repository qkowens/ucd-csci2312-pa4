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
		bool noMove = true;
		int direction = -1;

		std::vector<int> advantages, food, agents, empties;

		for (int n = 0; n < s.array.size(); n++)
		{
			int temp = n;
			if (s.array[n] == ADVANTAGE)
				advantages.push_back(temp);
			if (s.array[n] == FOOD)
				food.push_back(temp);
			if (s.array[n] == SIMPLE || s.array[n] == STRATEGIC)
				agents.push_back(temp);
			if (s.array[n] == EMPTY)
				empties.push_back(temp);
		}

		if (!empties.empty())
			direction = empties[rand() % empties.size()];

		if (!food.empty())
			direction = food[rand() % food.size()];

		if (!advantages.empty())
			direction = advantages[rand() % advantages.size()];

		if (!agents.empty() && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
			direction = agents[rand() % agents.size()];

		if (direction == 0)
			return NW;

		if (direction == 1)
			return N;

		if (direction == 2)
			return NE;

		if (direction == 3)
			return W;

		if (direction == 4)
			return STAY;

		if (direction == 5)
			return E;

		if (direction == 6)
			return SW;

		if (direction == 7)
			return S;

		if (direction == 8)
			return SE;

		return STAY;
	}
}

