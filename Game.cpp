//Quinn Owens
//Prof. Ivo Georgiev
//Intermediate Programming
//4/17/2016

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
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
    
    
	void Game::populate()
	{
	}

	Game::Game()
    {
        __width = 4;
        __height = 5;
    }
    
    Game::Game(unsigned width, unsigned height, bool manual) // note: manual population by default
    {
        __width = width;
        __height = height;
        
        if (manual)
        {
            
        }
        else
        {
            
        }
    }
    
    Game::Game(const Game &g)
    {
        
    }
    
    Game::~Game()
    {
        for (int i = 0; i < __grid.size(); i++)
            delete __grid[i];
    }
    
    unsigned int Game::getNumPieces() const
    {
        return (int)__grid.size();
    }
    
    unsigned int Game::getNumAgents() const
    {
        unsigned int answer = 0;
        
        for (int i = 0; i < __grid.size(); i++)
            if (__grid[i]->getType() == SIMPLE || __grid[i]->getType() == STRATEGIC)
                answer++;

        return answer;
    }
    unsigned int Game::getNumSimple() const
    {
        unsigned int answer = 0;
        
        for (int i = 0; i < __grid.size(); i++)
            if (__grid[i]->getType() == SIMPLE)
                answer++;
        
        return answer;
    }
    unsigned int Game::getNumStrategic() const
    {
        unsigned int answer = 0;
        
        for (int i = 0; i < __grid.size(); i++)
            if (__grid[i]->getType() == STRATEGIC)
                answer++;
        
        return answer;
    }
    unsigned int Game::getNumResources() const
    {
        unsigned int answer = 0;
        
        for (int i = 0; i < __grid.size(); i++)
            if (__grid[i]->getType() == FOOD || __grid[i]->getType() == ADVANTAGE)
                answer++;
        
        return answer;
    }
    
    const Piece * Game::getPiece(unsigned int x, unsigned int y) const
    {
        for (int i = 0; i < getNumPieces(); i++)
            if (__grid[i]->getPosition().x == x && __grid[i]->getPosition().y == y)
                return __grid[i];
        return __grid[0];
    }
    
    void Game::addSimple(const Position &position)
    {
        __grid.push_back(new Simple(*this, position, NUM_INIT_AGENT_FACTOR));
    }
    
    void Game::addSimple(const Position &position, double energy) // used for testing only
    {
        __grid.push_back(new Simple(*this, position, energy));
    }
    
    void Game::addSimple(unsigned x, unsigned y)
    {
        __grid.push_back(new Simple(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR));
    }
    
    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        __grid.push_back(new Simple(*this, *new Position(x, y), energy));
    }
                         
    void Game::addStrategic(const Position &position, Strategy *s)
    {
        __grid.push_back(new Strategic(*this, position, NUM_INIT_AGENT_FACTOR, s));
    }
    
    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        __grid.push_back(new Strategic(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR, s));
    }
    
    void Game::addFood(const Position &position)
    {
        __grid.push_back(new Strategic(*this, position, NUM_INIT_AGENT_FACTOR));
    }
    
    void Game::addFood(unsigned x, unsigned y)
    {
        __grid.push_back(new Food(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR));
    }
    
    void Game::addAdvantage(const Position &position)
    {
        __grid.push_back(new Advantage(*this, position, NUM_INIT_AGENT_FACTOR));
    }
    
    void Game::addAdvantage(unsigned x, unsigned y)
    {
        __grid.push_back(new Advantage(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR));
    }
    
    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings s;
        
        if (getPiece(pos.x-1, pos.y-1)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x-1, pos.y-1)->getType();
        
        if (getPiece(pos.x-1, pos.y)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x-1, pos.y)->getType();
        
        if (getPiece(pos.x-1, pos.y+1)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x+1, pos.y-1)->getType();
        
        if (getPiece(pos.x, pos.y-1)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x, pos.y-1)->getType();
        
        if (getPiece(pos.x, pos.y+1)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x, pos.y+1)->getType();
        
        if (getPiece(pos.x+1, pos.y-1)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x+1, pos.y-1)->getType();
        
        if (getPiece(pos.x+1, pos.y)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x+1, pos.y)->getType();
        
        if (getPiece(pos.x+1, pos.y+1)->getType() != INACCESSIBLE)
            s.array[0] = getPiece(pos.x+1, pos.y+1)->getType();
        
        return s;
        
    }
    
    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
        return N;
    }
    
    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        switch(ac)
        {
            case NW:
            {
                if (pos.x > 0 && pos.y > 0) return true;
                else return false;
            }
            case N:
            {
                if (pos.x > 0) return true;
                else return false;
            }
            case NE:
            {
                if (pos.x > 0 && pos.y < __width-1) return true;
                else return false;
            }
            case W:
            {
                if (pos.y > 0) return true;
                else return false;
            }
            case E:
            {
                if (pos.y < __width-1) return true;
                else return false;
            }
            case SW:
            {
                if (pos.x < __width-1 && pos.y > 0) return true;
                else return false;
            }
            case S:
            {
                if (pos.x < __width-1) return true;
                else return false;
            }
            case SE:
            {
                if (pos.x < __width-1 && pos.y < __width-1) return true;
                else return false;
            }
                
            case STAY: return true;
        }
    }
    
    const Position Game::move(const Position &pos, const ActionType &ac) const // note: assumes legal, use with isLegal()
    {
        if (isLegal(ac, pos))
        {
            switch (ac)
            {
                case NW:    return *new Position(pos.x-1,pos.y-1);
                case N:     return *new Position(pos.x-1,pos.y);
                case NE:    return *new Position(pos.x-1,pos.y+1);
                case W:     return *new Position(pos.x,pos.y-1);
                case E:     return *new Position(pos.x,pos.y+1);
                case SW:    return *new Position(pos.x+1,pos.y-1);
                case S:     return *new Position(pos.x+1,pos.y);
                case SE:    return *new Position(pos.x+1,pos.y+1);
                case STAY:  return pos;
            }
        }
        return pos;
    }
    
    void Game::round()   // play a single round
    {
        
    }
    
    void Game::play(bool verbose)
    {
        
    }
	std::ostream & operator<<(std::ostream & os, const Game & game)
	{
		return os;
	}
}






