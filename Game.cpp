//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2016

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
#include <set>
#include <sstream>
#include "Food.h"
#include "Advantage.h"
#include "Simple.h"
#include "Strategic.h"
#include "Piece.h"
#include "Game.h"
#include "Gaming.h"
#include "DefaultAgentStrategy.h"

namespace Gaming
{
    
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
	PositionRandomizer Game::__posRandomizer;
    
	void Game::populate()
	{
		std::default_random_engine rand;
		std::uniform_int_distribution<int> d(0, __width * __height);

		__numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
		__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
		unsigned int numStrategic = __numInitAgents / 2;
		unsigned int numSimple = __numInitAgents - numStrategic;
		unsigned int numAdvantages = __numInitResources / 4;
		unsigned int numFoods = __numInitResources - numAdvantages;

		while (numStrategic > 0)
		{
			int it = d(rand);
			if (it != (__width * __height) && __grid[it] == nullptr)
			{
				Position temp(it / __width, it % __width);
				__grid[it] = new Strategic(*this, temp, STARTING_AGENT_ENERGY);
				numStrategic--;
			}
		}

		while (numSimple > 0)
		{
			int it = d(rand);
			if (it != (__width * __height) && __grid[it] == nullptr)
			{
				Position temp(it / __width, it % __width);
				__grid[it] = new Simple(*this, temp, STARTING_AGENT_ENERGY);
				numSimple--;
			}
		}

		while (numFoods > 0)
		{
			int it = d(rand);
			if (it != (__width * __height) && __grid[it] == nullptr)
			{
				Position temp(it / __width, it % __width);
				__grid[it] = new Food(*this, temp, STARTING_RESOURCE_CAPACITY);
				numFoods--;
			}
		}

		while (numAdvantages > 0)
		{
			int it = d(rand);
			if (it != (__width * __height) && __grid[it] == nullptr)
			{
				Position temp(it / __width, it % __width);
				__grid[it] = new Advantage(*this, temp, STARTING_RESOURCE_CAPACITY);
				numAdvantages--;
			}
		}
	}

	Game::Game() : __width(3), __height(3)
    {
		for (unsigned pos = 0; pos < (__width * __height); ++pos)
			__grid.push_back(nullptr);

		__status = NOT_STARTED;
		__verbose = false;
		__round = 0;
    }
    
    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height)
    {
		if (width < MIN_WIDTH || height < MIN_HEIGHT)
			throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        
		__status = NOT_STARTED;
		__verbose = false;
		__round = 0;

		for (unsigned pos = 0; pos < (__width * __height); ++pos)
			__grid.push_back(nullptr);

        if(!manual)
			populate();
    }
    
    Game::Game(const Game &g)
    {
        
    }
    
    Game::~Game()
	{
		for (auto it = __grid.begin(); it != __grid.end(); ++it)
		{
			if (*it != nullptr)
			{
				delete *it;
			}
		}
	}
    
    unsigned int Game::getNumPieces() const
    {
		int answer = 0;

		for (int pos = 0; pos < __grid.size(); pos++)
			if (__grid[pos] != nullptr)
				answer++;

        return answer;
    }
    
    unsigned int Game::getNumAgents() const
    {
		int answer = 0;

		for (int pos = 0; pos < __grid.size(); pos++)
			if (__grid[pos] != nullptr)
				if(__grid[pos]->getType() == SIMPLE || __grid[pos]->getType() == STRATEGIC)
					answer++;

		return answer;
    }
    unsigned int Game::getNumSimple() const
    {
		int answer = 0;

		for (int pos = 0; pos < __grid.size(); pos++)
			if (__grid[pos] != nullptr)
				if (__grid[pos]->getType() == SIMPLE)
					answer++;

		return answer;
    }
    unsigned int Game::getNumStrategic() const
    {
		int answer = 0;

		for (int pos = 0; pos < __grid.size(); pos++)
			if (__grid[pos] != nullptr)
				if (__grid[pos]->getType() == STRATEGIC)
					answer++;

		return answer;
    }
    unsigned int Game::getNumResources() const
    {
		int answer = 0;

		for (int pos = 0; pos < __grid.size(); pos++)
			if (__grid[pos] != nullptr)
				if (__grid[pos]->getType() == ADVANTAGE || __grid[pos]->getType() == FOOD)
					answer++;

		return answer;
    }
    
    const Piece * Game::getPiece(unsigned int x, unsigned int y) const
    {
		if (x > __width || y > __height)
			throw OutOfBoundsEx(__width, __height, x, y);
		for (int it = 0; it < __grid.size(); it++)
		{
			if (__grid[it] != nullptr)
				if (__grid[it]->getPosition().x == x && __grid[it]->getPosition().y == y)
					return __grid[it];
		}
		throw PositionEmptyEx(x, y);
        return __grid[0];
    }
    
    void Game::addSimple(const Position &position)
    {
		int pos = position.y + (position.x * __width);

		if (position.y >= __width || position.x >= __height) 
			throw OutOfBoundsEx(__width, __height, position.x, position.y);

		if (__grid[pos]) 
			throw PositionNonemptyEx(position.x, position.y);

		__grid[pos] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }
    
    void Game::addSimple(const Position &position, double energy) // used for testing only
    {
		int pos = position.y + (position.x * __width);

		if (position.y >= __width || position.x >= __height)
			throw OutOfBoundsEx(__width, __height, position.x, position.y);

		if (__grid[pos])
			throw PositionNonemptyEx(position.x, position.y);

		__grid[pos] = new Simple(*this, position, energy);
    }
    
    void Game::addSimple(unsigned x, unsigned y)
    {
		int pos = y + (x * __width);

		if (y >= __width || x >= __height)
			throw OutOfBoundsEx(__width, __height, x, y);

		if (__grid[pos])
			throw PositionNonemptyEx(x, y);

		Position position(x, y);

		__grid[pos] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }
    
    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
		int pos = y + (x * __width);

		if (y >= __width || x >= __height)
			throw OutOfBoundsEx(__width, __height, x, y);

		if (__grid[pos])
			throw PositionNonemptyEx(x, y);

		Position position(x, y);

		__grid[pos] = new Simple(*this, position, energy);
    }
                         
    void Game::addStrategic(const Position &position, Strategy *s)
    {
		int pos = position.y + (position.x * __width);

		if (position.y >= __width || position.x >= __height)
			throw OutOfBoundsEx(__width, __height, position.x, position.y);

		if (__grid[pos])
			throw PositionNonemptyEx(position.x, position.y);

		__grid[pos] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }
    
    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
		int pos = y + (x * __width);

		if (y >= __width || x >= __height)
			throw OutOfBoundsEx(__width, __height, x, y);

		if (__grid[pos])
			throw PositionNonemptyEx(x, y);

		Position position(x, y);

		__grid[pos] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }
    
    void Game::addFood(const Position &position)
    {
		int pos = position.y + (position.x * __width);

		if (position.y >= __width || position.x >= __height)
			throw OutOfBoundsEx(__width, __height, position.x, position.y);

		if (__grid[pos])
			throw PositionNonemptyEx(position.x, position.y);

		__grid[pos] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    
    void Game::addFood(unsigned x, unsigned y)
    {
		int pos = y + (x * __width);

		if (y >= __width || x >= __height)
			throw OutOfBoundsEx(__width, __height, x, y);

		if (__grid[pos])
			throw PositionNonemptyEx(x, y);

		Position position(x, y);

		__grid[pos] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    
    void Game::addAdvantage(const Position &position)
    {
		int pos = position.y + (position.x * __width);

		if (position.y >= __width || position.x >= __height)
			throw OutOfBoundsEx(__width, __height, position.x, position.y);

		if (__grid[pos])
			throw PositionNonemptyEx(position.x, position.y);

		__grid[pos] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    
    void Game::addAdvantage(unsigned x, unsigned y)
    {
        int pos = y + (x * __width);

		if (y >= __width || x >= __height)
			throw OutOfBoundsEx(__width, __height, x, y);

		if (__grid[pos])
			throw PositionNonemptyEx(x, y);

		Position position(x, y);

		__grid[pos] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    
    const Surroundings Game::getSurroundings(const Position &pos) const
    {
		Surroundings s;
		for (int pos = 0; pos < 9; ++pos)
			s.array[pos] = EMPTY;

		for (int row = -1; row <= 1; ++row)
		{
			for (int col = -1; col <= 1; ++col)
			{
				if (pos.x + row >= 0 && pos.x + row < __height
					&& pos.y + col >= 0 && pos.y + col < __width)
				{
					unsigned int it = pos.y + col + ((pos.x + row) * __width);

					if (__grid[it])
						s.array[col + 1 + ((row + 1) * 3)] = __grid[it]->getType();
				}
				else
					s.array[col + 1 + ((row + 1) * 3)] = INACCESSIBLE;
			}
		}
		s.array[4] = SELF;

		return s;
        
    }
    
    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
		int x;
		int y;

		x = to.x - from.x;
		y = to.y - from.y;

		x++;
		y++;

		unsigned int pos = (y + (x * 3));

		switch (pos)
		{
		case 0: return NW;
		case 1: return N;
		case 2: return NE;
		case 3: return W;
		case 4: return STAY;
		case 5: return E;
		case 6: return SW;
		case 7: return S;
		case 8: return SE;
		default: return STAY;
		}
    }
    
    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
		int x, y;

		x = pos.x;
		y = pos.y;

		switch (ac)
		{
		case E: y++; 
			break;
		case NE: y++; 
			x--; 
			break;
		case N: x--; 
			break;
		case NW: y--;
			x--; 
			break;
		case W: y--; 
			break;
		case SW: y--; 
			x++; 
			break;
		case S: x++;
			break;
		case SE: x++; 
			y++; 
			break;
		default: break;
		}

		Position p((unsigned)x, (unsigned)y);

		if (p.x < __height && p.y < __width)
			return true;

		return false;
    }
    
    const Position Game::move(const Position &pos, const ActionType &ac) const // note: assumes legal, use with isLegal()
    {
		if (isLegal(ac, pos))
		{
			int x, y;
			x = pos.x;
			y = pos.y;
			switch (ac)
			{
			case E: y++; 
				break;
			case NE: y++; 
				x--; 
				break;
			case N: 
				x--; 
				break;
			case NW: y--; 
				x--; 
				break;
			case W: y--; 
				break;
			case SW: y--; 
				x++; 
				break;
			case S: x++; 
				break;
			case SE: x++;
				y++; 
				break;
			default: break;
			}

			Position p((unsigned)x, (unsigned)y);

			return p;
		}
		return pos;
    }
    
    void Game::round()   // play a single round
    {
		std::set<Piece*> pieces;
		for (auto it = __grid.begin(); it != __grid.end(); ++it)
		{
			if (*it)
			{
				pieces.insert(pieces.end(), *it);
				(*it)->setTurned(false);
			}
		}

		// Take turns
		for (auto it = pieces.begin(); it != pieces.end(); ++it)
		{
			if (!(*it)->getTurned())
			{
				(*it)->setTurned(true);
				(*it)->age();

				ActionType ac = (*it)->takeTurn(getSurroundings((*it)->getPosition()));
				Position pos0 = (*it)->getPosition();
				Position pos1 = move(pos0, ac);

				if (pos0.x != pos1.x || pos0.y != pos1.y)
				{
					Piece *p = __grid[pos1.y + (pos1.x * __width)];
					if (p)
					{
						(*(*it)) * (*p);
						if ((*it)->getPosition().x != pos0.x || (*it)->getPosition().y != pos0.y)
						{
							// piece moved
							__grid[pos1.y + (pos1.x * __width)] = (*it);
							__grid[pos0.y + (pos0.x * __width)] = p;
						}
					}
					else
					{
						// empty move
						(*it)->setPosition(pos1);
						__grid[pos1.y + (pos1.x * __width)] = (*it);
						__grid[pos0.y + (pos0.x * __width)] = nullptr;
					}
				}
			}
		}

		// Update positions and delete unviable first
		for (unsigned int i = 0; i < __grid.size(); ++i)
			if (__grid[i] && !(__grid[i]->isViable()))
			{
				delete __grid[i];
				__grid[i] = nullptr;
			}

		// Check game over
		if (getNumResources() <= 0)
			__status = Status::OVER;

		__round++;
    }
    
    void Game::play(bool verbose)
    {
		__verbose = verbose;
		__status = PLAYING;
		std::cout << *this;
		while (__status != OVER)
		{
			round();
			if (verbose) std::cout << *this;
		}
		if (!verbose) std::cout << *this;
    }
	std::ostream & operator<<(std::ostream & os, const Game & game)
	{
		os << "Round " << game.__round << std::endl;

		int column = 0;

		for (auto it = game.__grid.begin(); it != game.__grid.end(); ++it)
		{
			if (*it == nullptr)
				os << "[" << std::setw(6) << "]";

			else
			{
				std::stringstream ss;
				ss << "[" << **it;
				std::string str;
				std::getline(ss, str);
				os << str << "]";
			}
			if (++column == game.__width)
			{
				column = 0;
				os << std::endl;
			}
		}
		os << "Status: ";
		switch (game.getStatus())
		{
		case Game::Status::NOT_STARTED:
			std::cout << "Not Started..." << std::endl; 
			break;
		case Game::Status::PLAYING:
			std::cout << "Playing..." << std::endl; 
			break;
		default:
			std::cout << "Over!" << std::endl; 
			break;
		}

		return os;
	}
}






