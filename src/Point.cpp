#include "Point.h"


Point::Point()
{
}

Point::~Point()
{
}
// Set point num function
void Point::setPointNum(const int num)
{
	m_PointNum = num;
}
// Get point num function
int Point::getPointNum()
{
	return m_PointNum;
}
// Set edges num for each point
void Point::setEdgesNum(const int& num)
{
	m_EdgesNum = num;
}
// Set edges angle 
void Point::setEdges(const char& c, sf::RectangleShape& edge)
{
	switch (c)
	{
	case 'a':
		edge.setRotation(A);
		break;
	case 'b':
		edge.setRotation(B);
		break;
	case 'c':
		edge.setRotation(C);
		break;
	case 'd':
		edge.setRotation(D);
		break;
	case 'e':
		edge.setRotation(E);
		break;
	case 'f':
		edge.setRotation(F);
		break;
	}

	m_edegs.push_back(edge);
}
// Locate x function
void Point::setLocationX(const float x)
{
	m_location_x = x;
}
// Locate y function
void Point::setLocationY(const float y)
{
	m_location_y = y;
}
// Set point function
void Point::setPoint(sf::CircleShape& circle)
{
	m_point = circle;
}
// Get x location
float Point::getLocationX()
{
	return m_location_x;
}
// Get y location
float Point::getLocationY()
{
	return m_location_y;
}
// Rotate edges
void Point::MySetRotation(const float num)
{
	for (int j=0; j < m_EdgesNum; j++)
		m_edegs[j].rotate(num);
	
}
// get edges num
int Point::getEdgesNum()
{
	return m_EdgesNum;
}
// get point shape
sf::CircleShape Point::getPointShape()
{
	return m_point;
}
// Draw Point & edges
void Point::Draw(sf::RenderWindow& window) const
{
	for (auto i : m_edegs)
		window.draw(i);

	window.draw(m_point);
}
// Set num of neighbors
void Point::setNumOfNeighbors(const int num)
{
	m_numOfNeighbors = num;
}
// set neighbors into vector
void Point::setNeighbors(const int neighbor)
{
	m_neighbors.push_back(neighbor);
}
// get num of neighbors
int Point::getNumOfNeighbors()
{
	return m_numOfNeighbors;
}
// get neighbors vector
std::vector<int> Point::getNeighborsVec()
{
	return m_neighbors;
}
// get edges index
sf::RectangleShape Point::getEdgesIndex(const int index)
{
	return m_edegs[index];
}
// set point color function
void Point::setPointColor(sf::Color color)
{
	m_point.setFillColor(color);
}


