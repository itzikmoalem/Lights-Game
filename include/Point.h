#pragma once
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Point
{
public:
	Point();
	~Point();

	void setPointNum(const int num);
	int getPointNum();

	void setEdgesNum(const int& num);
	int getEdgesNum();

	void setLocationX(const float x);
	void setLocationY(const float y);

	float getLocationX();
	float getLocationY();

	void MySetRotation(const float num);

	void setPoint(sf::CircleShape& circle);
	void setEdges(const char& c, sf::RectangleShape& edge);

	sf::CircleShape getPointShape();

	void Draw(sf::RenderWindow& window) const;

	void setNumOfNeighbors(const int num);
	void setNeighbors(const int neighbor);
	int getNumOfNeighbors();

	std::vector<int> getNeighborsVec();

	sf::RectangleShape getEdgesIndex(const int index);

	void setPointColor(sf::Color color);


private:
	sf::CircleShape m_point;
	std::vector <sf::RectangleShape> m_edegs;

	int m_PointNum;
	int m_EdgesNum;

	float m_location_x,
		  m_location_y;

	std::vector<int> m_neighbors;
	int m_numOfNeighbors;
};


