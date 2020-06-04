#pragma once

#include <fstream>
#include <string>
#include "Utilities.h"
#include "Point.h"
#include "Manager.h"
#include <list>

class Game
{
public:

	Game();

	void run(Manager &mang);

	void LoadFile();
	void ReadLevel();
	void TakeEvent(sf::RenderWindow& window);

	void Rotation(const float rot, const sf::Vector2f MousePos);

	sf::Vector2f getBoardInformation();
	bool WinLevel();

private:

	std::vector<std::unique_ptr<Point>> m_Points;
	std::vector<bool> m_Power;

	std::ifstream m_file;

	int m_NumOfPoints = 0;
	int m_Rows = 0;
	int m_Middle = 0;

	double m_PointSize = 10;

	bool m_LevelComplete = false;
	bool m_Game = false;

	void PrintBoard(sf::RenderWindow& window);
	bool connectionCheck(Point& point);
	Point& getPoint(const int index);

};
