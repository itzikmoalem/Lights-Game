#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "string"
#include "Utilities.h"

using std::string;

// The class manager mention to be the class that loading the whole textures, needed to be used in the game.
class Manager
{
public:
	
	Manager(); // Constractor

	void LoadTexture(const int& num, const string& name); // Loading texture function
	sf::Texture& GetTexture(const int& num);			// Getting texture function

private:

	std::vector<sf::Texture> m_textures;
};