#include "Manager.h"

Manager::Manager()
{
	//resize the texture vector
	m_textures.resize(TEXTURES_SIZE);
}

// Loading texture function
void Manager::LoadTexture(const int& num, const string& name)
{
	m_textures[num].loadFromFile(name);
	m_textures[num].setSmooth(1);
}

// Getting texture function
sf::Texture& Manager::GetTexture(const int& num)
{
	return this->m_textures[num];
}




