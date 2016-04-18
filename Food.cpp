//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/27/2016

#include<iomanip>
#include"Game.h"
#include"Resource.h"
#include"Food.h"

namespace Gaming
{
	const char Food::FOOD_ID = 'F';

	Food::Food(const Game & g, const Position & p, double capacity) : Resource(g, p, capacity)
	{
	}

	Food::~Food()
	{
	}

	void Food::print(std::ostream & os) const
	{
		os << this->FOOD_ID << std::left << std::setw(4) << this->__id;
		os << std::setw(0);
	}
}