#include "Game.h"
#include "..\include\Game.h"
#include <iostream>

using std::string;

Game::Game()
{
}

void Game::run(Manager& mang)
{
	//define window game
	auto window = sf::RenderWindow(sf::VideoMode(900, 900), "Lights - Niv & Itzik Games");

	LoadFile();

	while (!m_file.eof())
	{
		ReadLevel();

		const int SIZE_VEC = m_NumOfPoints + 1;

		sf::Sprite background;
		background.setTexture(mang.GetTexture(0));

		m_Power.resize(SIZE_VEC);

		for (auto i : m_Power)
			i = false;

		while (!m_LevelComplete)
		{
			window.clear();
			window.draw(background);

			PrintBoard(window);

			window.display();

			TakeEvent(window);

			if (WinLevel())
			{
				sf::Sprite win;
				win.setTexture(mang.GetTexture(5));

				window.clear();
				window.draw(win);
				window.display();

				sf::sleep(sf::milliseconds(3000));

				m_LevelComplete = true;
			}
		}
	}

	sf::Sprite finish;
	finish.setTexture(mang.GetTexture(6));

	window.clear();
	window.draw(finish);
	window.display();

	sf::sleep(sf::milliseconds(4000));
}

void Game::LoadFile()
{
	m_file.open(LEVELS);

	if (!m_file.is_open())
	{
		std::cerr << "The levels file cannot be open\n" << std::endl;
		exit(1);
	}
}

void Game::ReadLevel()
{
	int PointsInRow = 3;
	int max = 3;

	string line;
	string word;
	char c;

	if (m_LevelComplete)
	{
		m_Points.clear();
		m_LevelComplete = false;
	}
	m_file >> line;

	m_NumOfPoints = std::stoi(line);

	m_PointSize = POINT_SIZE / m_NumOfPoints;

	sf::Vector2f temp = getBoardInformation();	// Getting board informtion
	m_Rows = temp.y;
	m_Middle = (temp.x - 1);

	const float LengthEdge = E_SIZE / m_Rows;

	float space = (board_size / (m_Rows - 1));	// Calculate spaces
	float s_y = 0,
		s_x = (m_Middle - PointsInRow) / 2;

	for (int point = 1; point <= m_NumOfPoints; point++)
	{
		Point temppoint;
		sf::CircleShape tempCircle;

		// Reading Point number
		m_file >> word; 
		temppoint.setPointNum(stoi(word));

		// Define Circle temp
		tempCircle.setPosition({Xboard + (s_x * space), Yboard + (s_y * space)});
		tempCircle.setRadius(m_PointSize);
		tempCircle.setOrigin(tempCircle.getRadius(), -tempCircle.getRadius());
		tempCircle.setOutlineColor(sf::Color::White);
		tempCircle.setOutlineThickness(2);

		if (point == (m_NumOfPoints / 2)+1)	//Middle led
			tempCircle.setFillColor(sf::Color::Yellow);
		else
			tempCircle.setFillColor(sf::Color::Black);

		if (max == point && point < (m_NumOfPoints / 2))
		{
			s_y+=SPACE_Y;
			max += (++PointsInRow);
			s_x = ((m_Middle - PointsInRow) *SPACE_X);
		}

		else if (max == point && point > (m_NumOfPoints / 2))
		{
			max += (--PointsInRow);
			s_y+=SPACE_Y;
			s_x = (m_Middle - PointsInRow) *SPACE_X;
		}
		else
			++s_x;

		// Read edges number
		m_file >> word;
		temppoint.setEdgesNum(stoi(word));

		for (int j = 0; j < stoi(word); j++)
		{
			sf::RectangleShape edge;

			edge.setSize({ EDGE_WIDTH, LengthEdge });
			edge.setFillColor(sf::Color::Magenta);
			edge.setOrigin(edge.getSize().x /2 , -tempCircle.getRadius()*1.4);
			edge.setPosition({ tempCircle.getPosition().x, tempCircle.getPosition().y +	20});

			try {
				m_file >> c;
				if (c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f')
					throw std::runtime_error::runtime_error("You have to use small letters 'a-f' for angle.\n");
			}
			catch (std::exception & e)
			{
				std::cerr << e.what() << std::endl;
				exit(1);
			}

			temppoint.setEdges(c, edge);
		}

		//Reading number of neighbors and set
		m_file >> word;
		temppoint.setNumOfNeighbors(stoi(word));

		try 
		{
			m_file >> word;
			if (word != "-")
			{
				throw std::runtime_error::runtime_error("You miss '-' char for neighbors list.\n");
			}
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
			exit(1);
		}

		for (int j = 0; j < temppoint.getNumOfNeighbors(); j++)
		{
			m_file >> word;
			temppoint.setNeighbors(stoi(word));
		}

		temppoint.setPoint(tempCircle);

		m_Points.emplace_back(std::make_unique<Point>(temppoint));
	}
}
//Take event function
void Game::TakeEvent(sf::RenderWindow& window)
{
	if (auto event = sf::Event{}; window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonPressed:
		{
			sf::Vector2f MousePos;

			MousePos.x = sf::Mouse::getPosition(window).x;
			MousePos.y = sf::Mouse::getPosition(window).y;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				Rotation(ROTATION, MousePos);

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				Rotation(-ROTATION, MousePos);
		}
		break;
		}
	}
}
// Rotation edge function
void Game::Rotation(const float rot, const sf::Vector2f MousePos)
{
	Point MidPoint;

	for (auto& i : m_Points)
	{
		if (i->getPointShape().getGlobalBounds().contains(MousePos))
			i->MySetRotation(rot);

		if (i->getPointNum() == (m_NumOfPoints / 2) + 1)
			MidPoint = *i;
	}
	//Check edge connection function
	connectionCheck(MidPoint);
}

//This function collect information about the board size
sf::Vector2f Game::getBoardInformation()
{
	int sum = 0;
	int point = 3;	
	int count = 0;

	while (sum < m_NumOfPoints / 2)
	{
		sum += point;
		point++;				//point keep number of points to the middle of lines
		count++;
	}

	count += (count + 1);		//count keep number of lines

	sf::Vector2f moshe;
	moshe.x = float(point);
	moshe.y = float(count);
	return moshe;
}
//Print board function
void Game::PrintBoard(sf::RenderWindow& window)
{
	//Print all the points
	for (auto& i : m_Points)
		i->Draw(window);
}

//Using BFS Alghorithm
bool Game::connectionCheck(Point& s)
{
	const int SIZE_VEC = m_NumOfPoints + 1;
	// Mark all the vertices as not visited 
	std::vector<bool> visited;

	visited.resize(SIZE_VEC);

	for (int i = 0; i < m_NumOfPoints; i++)
		visited[i] = false;

	// Create a queue for BFS 
	std::list<Point> queue;

	// Mark the current node as visited and enqueue it 
	visited[s.getPointNum()] = true;
	queue.push_back(s);

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		s = queue.front();
		queue.pop_front();

		// Get all points of the dequeued 
		// If a point has not been visited, and we arrived to his edges  
		// mark it visited and enqueue it 
		for (int i=0; i < s.getNumOfNeighbors(); i++)
		{
			if (!visited[s.getNeighborsVec()[i]])// || !m_Power[s.getNeighborsVec()[i]])
			{
				for (int j = 0; j < s.getEdgesNum(); j++)
				{
					for (int k = 0; k < getPoint(s.getNeighborsVec()[i]).getEdgesNum(); k++)
					{
						Point neighbor = getPoint(s.getNeighborsVec()[i]);

						//if two egdes met each other
						if ((s.getEdgesIndex(j).getGlobalBounds().intersects(neighbor.getEdgesIndex(k).getGlobalBounds())))
						{
							queue.push_back(getPoint(s.getNeighborsVec()[i]));

							m_Power[neighbor.getPointNum()] = true;
							getPoint(s.getNeighborsVec()[i]).setPointColor(sf::Color::Yellow);
						}
						else
						{
							m_Power[neighbor.getPointNum()] = false;

							for (auto o : queue)
							{
								if (!visited[o.getPointNum()])
									m_Power[o.getPointNum()] = true;
							}
						}
					}
				}
				visited[s.getNeighborsVec()[i]] = true;
			}
		}
		//Checking for each point the visit and power status
		for (int m = 1; m < m_Power.size(); m++)
		{
			if (!m_Power[m] && visited[m] && m != ((m_NumOfPoints/2)+1))
				getPoint(m).setPointColor(sf::Color::Black);
			else if(m_Power[m] && !visited[m] && m != ((m_NumOfPoints / 2) + 1))
				getPoint(m).setPointColor(sf::Color::Black);
			if (visited[m] && !m_Power[m])
				visited[m] = false;
		}
	}
	return true;
}
// Return Point by iterator
Point& Game::getPoint(const int index)
{
	const int Index = index - 1;
	for (auto m = m_Points.begin(); m != m_Points.end(); m++)
		return *m[Index];

	return *m_Points[0];
}
// Level up function
bool Game::WinLevel()
{
	for (int i = 1; i < m_Power.size(); i++)
	{
		if (!m_Power[i])
			return false;
	}
	return true;
}
