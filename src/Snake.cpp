#include "Snake.h"

Snake::Snake() {

	for (int i = 0; i < tailCountStart; i++) {
		AddNewTail();
	}

}

void Snake::AddNewTail()
{
	Tail* newTail = new Tail;

	AddTail(newTail);

	tailCount++;

}

void Snake::AddTail(Tail* newTail)
{
	tails.push_back(newTail);
	
}

void Snake::MoveTail()
{
	tailFirst = tails.back();
	tails.pop_back();

	tailFirst->tailCoord[0] = posX;
	tailFirst->tailCoord[1] = posY;

	tails.push_front(tailFirst);

}

void Snake::ResetTail() {
	for (int i = 0; i < tailCount; i++) {
		MoveTail();
	}
}

bool Snake::isAlive()
{
	if (this->health > 0) {
		return true;
	}

	return false;
}

void Snake::setHealth(int newHealth)
{
	this->health = newHealth;
}

std::vector<int> Snake::getPos()
{
	return std::vector<int>{posX, posY};
}

std::vector<int> Snake::getNextPos()
{

	std::vector<int> nextPotentialPos{ posX,posY };
	switch (direction)
	{
	case Directions::RIGHT: {
		nextPotentialPos[0]++;
	}break;

	case Directions::LEFT: {
		nextPotentialPos[0]--;
	}break;

	case Directions::UP: {
		nextPotentialPos[1]--;
	}break;

	case Directions::DOWN: {
		nextPotentialPos[1]++;
	}break;

	default:
		break;
	}


	return nextPotentialPos;
}

std::vector<Coord2D> Snake::getAllTails()
{
	std::vector<Coord2D> tailCoords;
	for (int i = 0; i < tailCount; i++) {
		tailCoords.push_back(tails.at(i)->tailCoord);
	}

	return tailCoords;
}

void Snake::setPos(std::vector<int> newPos)
{
	posX = newPos[0];
	posY = newPos[1];
}

bool Snake::isBoostActive()
{
	return boost;
}

void Snake::BoostActivate()
{
	this->boost = true;
}

void Snake::BoostDisable()
{
	this->boost = false;
}

void Snake::setScore(int newScore)
{
	this->score = newScore;
}

int Snake::getScore()
{
	return this->score;
}

std::string Snake::getPlayerName()
{
	return this->playerName.c_str();
}

void Snake::setPlayerName(std::string newName)
{
	this->playerName = newName.c_str();
}

Directions Snake::getDirection()
{
	return direction;
}

void Snake::setDirection(Directions newDirection)
{
	this->direction = newDirection;
}

const char Snake::getTileView()
{
	return this->tileView;
}

void Snake::setTileView(char newView)
{
	tileView = newView;
	setTailTileView(100 + newView);
}

const char Snake::getTailTileView()
{
	return this->tileViewTail;
}

void Snake::setTailTileView(char newView)
{
	tileViewTail = newView;
}

void Snake::NextStep()
{
	MoveTail();

	switch (direction)
	{
	case Directions::RIGHT: {
		posX++;
	}break;

	case Directions::LEFT: {
		posX--;
	}break;

	case Directions::UP: {
		posY--;
	}break;

	case Directions::DOWN: {
		posY++;
	}break;

	default:
		break;
	}

}
