#include <iostream>
#include "GameModel.h"
#include <ctime>
#include "HumanCLIPlayer.h"

using namespace std;

int main()
{
	cout << "Running patchsim\n";

	// Init RNG used for shuffling
	// TODO is this still needed after switching to cpp rng
	srand((unsigned)time(0));

	GameModel game(2);
	unique_ptr<Player> p1 = make_unique<HumanCLIPlayer>();
	unique_ptr<Player> p2 = make_unique<HumanCLIPlayer>();
	game.addPlayer(0, std::move(p1));
	game.addPlayer(1, std::move(p2));
	game.startGame();

	return 0;
}