#include "GameModel.h"

#include <iostream>

#include <string>


using namespace std;



GameModel::GameModel(int num_players) :
	m_num_players(num_players),
	m_patchlist("..\\res\\patches.txt")
{
	m_boards.resize(m_num_players);
}

GameModel::~GameModel()
{
}




