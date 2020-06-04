#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using std::string;

//Level const
const string LEVELS = "Levels.txt";

//Texture consts
const string BACKGROUNG = "Lights-background.png";
const string NEWGAME = "NewGame.png";
const string NEWGAME_PRESSED = "NewGamePressed.png";
const string EXITGAME = "ExitGame.png";
const string EXITGAME_PRESSED = "ExitGamePressed.png";
const string LEVELUP = "Lights-levelup.png";
const string GAMECOMPLETE = "Lights-finish.png";

//Enums 
enum Elemnts
{
	E_BackGround, E_NewGame, E_NewGamePressed, E_ExitGame, E_ExitGamePressed, M_LevelUp, M_Gamefinish
};

//Setting consts
const int TEXTURES_SIZE = 7;	//texture's vector size 

const int BUTTON_WIDTH = 232;	//button's size
const int BUTTON_LENGTH = 53;

const float NEWGAME_POS_X = 355;	//button's locations
const float NEWGAME_POS_Y = 526;	
const float EXITGAME_POS_X = NEWGAME_POS_X;
const float EXITGAME_POS_Y = NEWGAME_POS_Y + 60;
const double LOWER_N = 0.84;
const double LOWER_E = 0.85;

const int POINT_SIZE = 190;
const int EDGE_WIDTH = 5;
const int EDGE_LENGTH = (POINT_SIZE / 20) * 6;
const int E_SIZE = 350;

// Edge Direction
const auto A = 270.f;
const auto B = 330.f;
const auto C = 30.f;
const auto D = 90.f;
const auto E = 150.f;
const auto F = 210.f;
const auto ROTATION = 60.f;

//
const auto board_size = 760;
const auto Xboard = 195;
const auto Yboard = 230;

const double SPACE_Y = 0.87;
const double SPACE_X = 0.5;

