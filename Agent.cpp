//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2015

#include"Game.h"
#include"Piece.h"
#include"Agent.h"
#include"Resource.h"

namespace Gaming
{
	const double Agent::AGENT_FATIGUE_RATE = 0.3;

	Agent::Agent(const Game & g, const Position & p, double energy) : Piece(g,p)
	{
		__energy = energy;
	}

	Agent::~Agent()
	{
	}

	void Agent::age()
	{
		__energy -= AGENT_FATIGUE_RATE;
		if (!this->isViable())
			finish();
	}

	Piece & Agent::operator*(Piece & other)
	{
		return other.interact(this);
	}
	Piece & Agent::interact(Agent *operand)
	{
		if (this->__energy > operand->__energy)
		{
			this->__energy -= operand->__energy;
			operand->finish();
		}
		else if (this->__energy = operand->__energy)
		{
			this->finish();
			operand->finish();
		}
		if (this->__energy < operand->__energy)
		{
			operand->__energy -= this->__energy;
			this->finish();
		}
		return *this;
	}

	Piece & Agent::interact(Resource *operand)
	{
		if (operand->getType() == FOOD)
			__energy += operand->consume();
		else if (operand->getType() == ADVANTAGE)
			__energy *= operand->consume();
		return *this;
	}

}