#include "Game.h"

Snake* Game::CreateNewSnake()
{
	this->snakeCount += 1;
	Snake* snake = new Snake;
	snake->setTileView(snakeCount - 1);
	snakeList.push_back(snake);

	return snake;
}

Snake* Game::CreateNewSnake(int CoordX, int CoordY)
{
	this->snakeCount += 1;
	Snake* snake = new Snake;

	snake->setTileView(snakeCount - 1);
	snake->setPos({ CoordX, CoordY });
	//snake.setPlayerName = "Snake" + std::to_string()
	snakeList.push_back(snake);

	return snake;
}

void Game::setActiveSnake(Snake& snake)
{
	this->activeSnake = &snake;
}

void Game::DeleteSnake(int index)
{
	snakeList.erase(snakeList.begin() + index);
}

void Game::DeleteAllSnakes()
{
	snakeList.clear();
}

void Game::Start()
{
	OnLoop();
}

void Game::KeyboardInput()
{
	if (IsKeyDown(KEY_DOWN)) {
		activeSnake->setDirection(Directions::DOWN);
	}
	if (IsKeyDown(KEY_UP)) {
		activeSnake->setDirection(Directions::UP);
	}
	if (IsKeyDown(KEY_LEFT)) {
		activeSnake->setDirection(Directions::LEFT);
	}
	if (IsKeyDown(KEY_RIGHT)) {
		activeSnake->setDirection(Directions::RIGHT);
	}
}

int Game::NextStepCollisionCheck(Snake snake)
{
	MapTileChar nextTile = map->getTile(snake.getNextPos()[0], snake.getNextPos()[1]);

	if (MapTileChars[MapTileID::EMPTY] == nextTile) {
		return MapTileID::EMPTY;
	}
	else if (MapTileChars[MapTileID::WALL] == nextTile) {
		return MapTileID::WALL;
	}
	else if (MapTileChars[MapTileID::SCORE] == nextTile) {
		return MapTileID::SCORE;
	}
	else if (MapTileChars[MapTileID::BOOST] == nextTile) {
		return MapTileID::BOOST;
	}
	else if (MapTileChars[MapTileID::UNKNOWNTILE] == nextTile) {
		return MapTileID::UNKNOWNTILE;
	}
	return -1;
}

void Game::UpdateMap()
{
	map->UpdateMap();

	for (int i = 0; i < snakeCount; i++) {

		//Update Snakes head
		map->setTile(snakeList[i]->getPos()[0], snakeList[i]->getPos()[1], snakeList[i]->getTileView());

		//Update Tails
		std::vector<Coord2D> Coords = snakeList[i]->getAllTails();
		for (int j = 0; j < Coords.size(); j++) {
			map->setTile(Coords[j][0], Coords[j][1], snakeList[i]->getTailTileView());
		}

	}

	//Update Score
	map->setTile(score.scorePos[0], score.scorePos[1], MapTileChars[MapTileID::SCORE]);

}

void Game::UpdateConsoleFrame()
{
	//ClearConsole();

	std::vector<std::vector<MapTileChar>> nmap = map->getMap();
	int height = map->getMaxHeight();
	int width = map->getMaxWidth();

	for (int i = 0; i < height; i++) {
		std::string buffer;
		buffer.reserve(width);
		for (int j = 0; j < width; j++) {
			buffer.push_back(nmap[i][j]);
		}
		std::cout << buffer.c_str();
		std::cout << std::endl;
	}

}

void Game::CreateScore()
{
	int mapW = map->getMaxWidth();
	int mapH = map->getMaxHeight();

	bool isPlaced = false;
	srand(time(NULL));

	int randX = rand() % (mapW - 1);
	int randY = rand() & (mapH - 1);

	if (map->getTile(randX, randY) == MapTileChars[MapTileID::EMPTY]) {
		map->setTile(randX, randY, MapTileChars[MapTileID::SCORE]);
		score.scorePos[0] = randX;
		score.scorePos[1] = randY;

		isPlaced = true;
	}
	else {
		int factor = 1;
		std::vector<std::vector<short>> vec = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1} };

		while (!isPlaced) {
			//HATALI!
			for (int i = 0; i < 8; i++) { // rastgele olması sağlanacak
				if (map->getTile(randX + (vec[i][0] * factor), randY + (vec[i][1] * factor)) == MapTileChars[MapTileID::EMPTY]) {
					map->setTile(randX + (vec[i][0] * factor), randY + (vec[i][1] * factor), MapTileChars[MapTileID::SCORE]);
					score.scorePos[0] = randX + (vec[i][0] * factor);
					score.scorePos[1] = randY + (vec[i][1] * factor);

					isPlaced = true;
					break;
				}
			}

			factor++;
		}
	}
}

void Game::GameNextStep()
{
	for (int i = 0; i < snakeCount; i++) {

		switch (NextStepCollisionCheck(*(snakeList[i]))) {
		case MapTileID::EMPTY: {
			snakeList[i]->NextStep();
			break;
		}

		case MapTileID::SCORE: {
			snakeList[i]->setScore(snakeList[i]->getScore() + 1);
			snakeList[i]->AddNewTail();
			snakeList[i]->NextStep();
			CreateScore();
			break;
		}

		case MapTileID::WALL: {

#if !TEST
			isRunning = false;
#endif // TEST
			break;
		}

		default: {

#if !TEST
			isRunning = false;
#endif 
		}

		}

	}
}

void Game::ReCreateMap(size_t mapWidht, size_t mapHeight)
{
	delete this->map;

	this->CreateMap(mapWidht, mapHeight);
	this->CreateScore();


}

Game::Game() {

	CreateMap();

	//Generate Score
	CreateScore();

}


Game::~Game()
{
	if (map != NULL) {
		delete map;
	}
	if (activeSnake != NULL) {
		delete activeSnake;
	}
}

void Game::OnLoop()
{
	std::chrono::duration<double, std::milli> timeElapsed;
	const int refRate = 120; // milli

	while (isRunning) {

		auto timeStart = std::chrono::high_resolution_clock::now();

		UpdateFrame();
		KeyboardInput();

		UpdateMap();
		GameNextStep();

		auto timeEnd = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> timeElapsed = timeEnd- timeStart;

		if (timeElapsed.count() < refRate) {
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(refRate - timeElapsed.count()));
		}


	}

}

void Game::CreateMap(size_t mapWidht, size_t mapHeight)
{
	Map* map = new Map(mapWidht, mapHeight);
	if (this->map == NULL) {
		this->map = map;
	}

	this->map = map;
}

void Game::CreateWindow()
{
	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(120);

	CreateMapVisuals(map->getMaxWidth(), map->getMaxHeight());
}

void Game::UpdateFrame()
{
	BeginDrawing();
	{
		ClearBackground(RAYWHITE);

		//Draw snakes
		for (size_t i = 0; i < snakeList.size(); i++) {
			DrawRectangleV(raylib::Vector2(
				snakeList[i]->getPos()[0] * cellWidth,
				snakeList[i]->getPos()[1] * cellHeight),
				raylib::Vector2(cellWidth, cellHeight),
				raylib::Color::Red()
			);

			std::vector<Coord2D> tails = snakeList[i]->getAllTails();
			size_t tailCount = snakeList[i]->getAllTails().size();
			for (size_t j = 0; j < tailCount; j++) {
				Tail tail = tails[j];
				DrawRectangleV(raylib::Vector2(
					tail.tailCoord[0] * cellWidth,
					tail.tailCoord[1] * cellHeight),
					raylib::Vector2(cellWidth, cellHeight),
					raylib::Color::DarkPurple());
			}
		}

		//Draw bait
		DrawRectangleV(raylib::Vector2(
			score.scorePos[0] * cellWidth,
			score.scorePos[1] * cellHeight),
			raylib::Vector2(cellWidth, cellHeight),
			raylib::Color::Blue()
		);
		Map2D map_ = map->getMap();

		for (size_t i = 0; i < map_.size(); i++) {
			for (size_t j = 0; j < map_[i].size(); j++) {
				if (map_[i][j] == MapTileChars[MapTileID::WALL]) {
					DrawRectangleV(raylib::Vector2(
						j * cellWidth,
						i * cellHeight),
						raylib::Vector2(cellWidth, cellHeight),
						raylib::Color::Black()
					);
				}
			}
		}

		//Draw vertical lines of map
		for (size_t i = 0; i < vertLinesOfMap.size(); i += 2) {
			DrawLineV(vertLinesOfMap[i], vertLinesOfMap[i + 1], raylib::Color::DarkGreen());
		}

		//Draw horizontal lines of map
		for (size_t i = 0; i < horLinesOfMap.size(); i += 2) {
			DrawLineV(horLinesOfMap[i], horLinesOfMap[i + 1], raylib::Color::DarkGreen());
		}


	}
	EndDrawing();

}

void Game::CreateMapVisuals(int cellCountX, int cellCountY)
{
	//Cell Creation

	cellWidth = static_cast<float>(screenWidth) / static_cast<float>(cellCountX);
	cellHeight = static_cast<float>(screenHeight) / static_cast<float>(cellCountY);

	//Top to bottm

	//	0---1
	//	|   |
	//	|   |
	//	|   |
	//	3---2

	for (int i = 0; i < cellCountX + 1; i++) {
		vertLinesOfMap.push_back(raylib::Vector2(cellWidth * i, 0));
		vertLinesOfMap.push_back(raylib::Vector2(cellWidth * i, screenHeight));
	}

	//Left to right

	//	0--------2
	//	|		 |
	//  1--------3

	for (int i = 0; i < cellCountY + 1; i++) {
		horLinesOfMap.push_back(raylib::Vector2(0, cellHeight * i));
		horLinesOfMap.push_back(raylib::Vector2(screenWidth, cellHeight * i));
	}

}

GameSingleP::GameSingleP() {
	this->snake = CreateNewSnake();

	ReCreateMap(12, 20);

	snake->setTileView(0);
	snake->setPos(std::vector<int>(5, 10));
	snake->ResetTail();

	setActiveSnake(*snake);

}

void GameSingleP::Start()
{
	this->CreateWindow();
	Game::Start();
}

