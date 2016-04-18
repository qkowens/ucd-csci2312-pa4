//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2016

#include<iomanip>
#include"Game.h"
#include"Resource.h"
#include"Advantage.h"

namespace Gaming
{
	const char Advantage::ADVANTAGE_ID = 'D';
	const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

	Advantage::Advantage(const Game & g, const Position & p, double capacity) : Resource(g, p, capacity)
	{
	}

	Advantage::~Advantage()
	{
	}

	void Advantage::print(std::ostream & os) const
	{
		os << ADVANTAGE_ID << std::left << std::setw(4) << __id;
		os << std::setw(0);
	}

	double Advantage::getCapacity() const
	{
		return __capacity;
	}

	double Advantage::consume()
	{
		finish();
		return __capacity*ADVANTAGE_MULT_FACTOR;
	}

}