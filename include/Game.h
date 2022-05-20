#pragma once
#include "Map.h"
#include "Snake.h"

#include <chrono>
#include <conio.h>
//#include <Windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <thread>
#include <mutex>

#include "raylib-cpp.hpp"
#include "extras/rnet.h"


#define WINDOWS 1
#define TEST false

using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;


static std::mutex keyboardMutex;
static std::mutex keyboardMutexStop;

typedef long long int llint;

struct GameOptions {

	int screenWidht = -1;
	int screenHeight = -1;
	unsigned int mapWidht = 12;
	unsigned int mapHeight = 20;
	
	double tilePerSecond = 0.0;

};

class Game
{
private:


	static const int defScreenWidth = 1280;
	static const int defScreenHeight = 720;

	int screenWidth = defScreenWidth;
	int screenHeight = defScreenHeight;

	bool isRunning = true;

	struct Score {
		Coord2D scorePos{ 0,0 };
	}score;

	Map* map;
	std::vector<Snake*> snakeList;
	Snake* activeSnake;
	int activePlayer = 0;
	int snakeCount = 0;

	std::chrono::duration<double, std::milli> refreshRateMSTick = std::chrono::milliseconds(8);// def 8
	std::chrono::duration<double, std::milli> refreshRateMSFps = std::chrono::milliseconds(16);// def 80

	void KeyboardInput();

	int NextStepCollisionCheck(Snake snake);

	void UpdateMap();
	void UpdateConsoleFrame();

	void OnLoop();

	std::string windowTitle = { "Snake" };

	raylib::Window window;

	std::vector<raylib::Vector2> vertLinesOfMap;
	std::vector<raylib::Vector2> horLinesOfMap;

	float cellWidth;
	float cellHeight;
	float lineSize;

	void CreateMapVisuals(int cellCountX, int cellCountY);
	void UpdateFrame();

	void CreateMap(size_t mapWidht = 12 , size_t mapHeight = 20);
	void CreateScore();

	void GameNextStep();


public:
	Game();
	~Game();

	Snake* CreateNewSnake();
	Snake* CreateNewSnake(int CoordX, int CoordY);

	void setActiveSnake(Snake &snake);
	void DeleteSnake(int index = 0);
	void DeleteAllSnakes();
	void CreateWindow();

	void ReCreateMap(size_t mapWidht = 12, size_t mapHeight = 20);

	void Start();

	static llint ConvertFPSToMs(llint fps) noexcept;
	static llint ConvertMsToFps(llint ms) noexcept;

};

class GameSingleP : public Game {

private:

	Snake* snake;
	

public:

	
	GameSingleP();
	void Start();


};
