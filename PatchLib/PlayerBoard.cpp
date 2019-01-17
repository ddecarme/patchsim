#include "PlayerBoard.h"
#include <iostream>

using namespace std;

PlayerBoard::PlayerBoard()
{
	cout << "Created playerboard\n";
}


PlayerBoard::~PlayerBoard()
{
	cout << "Destroy playerboard\n";
}

bool PlayerBoard::CheckPlacement(struct PatchPlacement& p)
{
	return false;
}

void PlayerBoard::AddPlacement(struct PatchPlacement& p)
{

}
