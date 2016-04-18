//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2016

#include"Game.h"
#include"Piece.h"
#include"Agent.h"
#include"Resource.h"

namespace Gaming
{
	const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

	Resource::Resource(const Game & g, const Position & p, double capacity) : Piece(g, p)
	{
		__capacity = capacity;
	}

	Resource::~Resource()
	{
	}

	double Resource::consume()
	{
		finish();
		return __capacity;
	}

	void Resource::age()
	{
		__capacity /= RESOURCE_SPOIL_FACTOR;
		if (!this->isViable())
			finish();
	}

	ActionType Resource::takeTurn(const Surroundings & s) const
	{
		return STAY;
	}

	Piece & Resource::operator*(Piece & other)
	{
		return other.interact(this);
	}

	Piece & Resource::interact(Agent *operand)
	{
		operand->addEnergy(consume());
		return *this;
	}

	Piece & Resource::interact(Resource *operand)
	{
		return *operand;
	}
}