#pragma once
#include <vector>
#include <string>
#include <queue>

typedef std::vector<int> Coord2D;

enum class Directions
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

struct Tail {
	Tail(std::vector<int> newTailCoords) {
		tailCoord = newTailCoords;
	}
	Tail(int posx = -1, int posy = -1) {
		tailCoord[0] = posx;
		tailCoord[1] = posy;
	}
	std::vector<int> tailCoord = {-1,-1};
};

class Snake {
private:

	int posX = 0;
	int posY = 0;
	int health = 1;
	int score = 0;
	int tailCount = 0;
	static const int tailCountStart = 3;
	bool boost = false;
	std::string playerName;
	Directions direction = Directions::UP;
	char tileView = 0;
	char tileViewTail = 100;
	
	Tail* tailFirst;
	
	std::deque<Tail*> tails;

	void AddTail(Tail* newTail);
	void MoveTail();

public:

	Snake();

	bool isAlive();
	void setHealth(int newHealth);

	//[0]-X  [1]-Y
	Coord2D getPos();
	Coord2D getNextPos();

	std::vector<Coord2D> getAllTails();

	void setPos(std::vector<int> newPos);

	bool isBoostActive();
	void BoostActivate();
	void BoostDisable();

	void setScore(int newScore);
	int  getScore();

	std::string getPlayerName();
	void setPlayerName(std::string newName);

	Directions getDirection();
	void setDirection(Directions newDirection);

	const char getTileView();
	void setTileView(char);

	const char getTailTileView();
	void setTailTileView(char);

	void NextStep();
	void ResetTail();

	void AddNewTail();
	
};

