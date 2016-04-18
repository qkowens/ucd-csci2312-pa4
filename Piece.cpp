//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2015

#include<string>

#include"Piece.h"
#include"Game.h"

namespace Gaming
{
	unsigned int Piece::__idGen = 0;

	Piece::Piece(const Game & g, const Position & p) : __game(g), __position(p)
	{
		__id = __idGen++;
		__finished = false;
		__turned = false;
	}

	Piece::~Piece()
	{
	}

	std::ostream & operator<<(std::ostream & os, const Piece & piece)
	{
		piece.print(os);
		return os;
	}
}