//Includes
#include <SFML/Graphics.hpp>
#include "Manager.h"
#include "Utilities.h"
#include "Game.h"

//Prototype
void LoadTextures(Manager& manager);
void DefineButtons(sf::Sprite &NewGame, sf::Sprite& ExitGame);
void ButtonEffect(sf::Sprite& NewGame, sf::Sprite& ExitGame, sf::RenderWindow &window, Manager &manager);
bool NewGameRectangle(const int MousePos_x, const int MousePos_y);
bool ExitGameRectangle(const int MousePos_x, const int MousePos_y);

//Main
int main()
{
	//define manager for load textures once
	Manager manager;
	Game game;
	bool gameRun = false;

	//define window menu
    auto window = sf::RenderWindow(sf::VideoMode(900, 900), "Lights - Niv & Itzik Games");

	//load textures
	LoadTextures(manager);

	//load background
	sf::Sprite background;
	background.setTexture(manager.GetTexture(0));

	//load buttons
	sf::Sprite NewGame, ExitGame;

	//define buttons setting
	DefineButtons(NewGame, ExitGame);

	//game loop
    while (window.isOpen())
    {
        window.clear();
		
		//draw background
		window.draw(background);

		//draw buttons
		ButtonEffect(NewGame, ExitGame, window, manager);
		window.draw(NewGame);
		window.draw(ExitGame);

		window.display();

		//get events from the user mouse
        if (auto event = sf::Event{}; window.waitEvent(event))
        {
            switch (event.type)
            {
				case sf::Event::Closed:
					window.close();
				break;
			
				case sf::Event::MouseButtonReleased:
				{
					const int MousePos_y = sf::Mouse::getPosition(window).y;
					const int MousePos_x = sf::Mouse::getPosition(window).x;

					if (NewGameRectangle(MousePos_x, MousePos_y))
					{
						gameRun = true;
						window.close();
					}
					
					if (ExitGameRectangle(MousePos_x, MousePos_y))
						return EXIT_SUCCESS;

					window.display();
				}
				break;
            }
        }
		if (gameRun)
			game.run(manager);
    }
}

//This function load textures by 2 arguments - Enum and const string from Utilities
void LoadTextures(Manager &manager)
{
	manager.LoadTexture(E_BackGround, BACKGROUNG);
	manager.LoadTexture(E_NewGame, NEWGAME);
	manager.LoadTexture(E_NewGamePressed, NEWGAME_PRESSED);
	manager.LoadTexture(E_ExitGame, EXITGAME);
	manager.LoadTexture(E_ExitGamePressed, EXITGAME_PRESSED);
	manager.LoadTexture(M_LevelUp, LEVELUP);
	manager.LoadTexture(M_Gamefinish, GAMECOMPLETE);
}

void DefineButtons(sf::Sprite& NewGame, sf::Sprite& ExitGame)
{
	//define loctions
	NewGame.setPosition(sf::Vector2f(NEWGAME_POS_X, NEWGAME_POS_Y));
	ExitGame.setPosition(sf::Vector2f(EXITGAME_POS_X, EXITGAME_POS_Y));
}

//This function make a special button effect
void ButtonEffect(sf::Sprite& NewGame, sf::Sprite& ExitGame, sf::RenderWindow& window, Manager& manager)
{
	const int MousePos_y = sf::Mouse::getPosition(window).y;
	const int MousePos_x = sf::Mouse::getPosition(window).x;

	//NewGameCheck
	if (NewGameRectangle(MousePos_x, MousePos_y))	
		NewGame.setTexture(manager.GetTexture(E_NewGamePressed));
	else
		NewGame.setTexture(manager.GetTexture(E_NewGame));

	//ExitGame check
	if (ExitGameRectangle(MousePos_x, MousePos_y))
		ExitGame.setTexture(manager.GetTexture(E_ExitGamePressed));
	else
		ExitGame.setTexture(manager.GetTexture(E_ExitGame));
}

//This function check if the postion of the mouse is on "NewGame" button
bool NewGameRectangle(const int MousePos_x, const int MousePos_y)
{
	if ((MousePos_x >= NEWGAME_POS_X && MousePos_x <= (NEWGAME_POS_X + (BUTTON_WIDTH * LOWER_N))) &&
		(MousePos_y >= NEWGAME_POS_Y && MousePos_y <= NEWGAME_POS_Y + BUTTON_LENGTH))
		return true;
	return false;
}

//This function check if the postion of the mouse is on "ExitGame" button
bool ExitGameRectangle(const int MousePos_x, const int MousePos_y)
{
	if ((MousePos_x >= EXITGAME_POS_X && MousePos_x <= (EXITGAME_POS_X + (BUTTON_WIDTH * LOWER_E))) &&
		(MousePos_y >= EXITGAME_POS_Y && MousePos_y <= EXITGAME_POS_Y + BUTTON_LENGTH))
		return true;
	return false;
}
