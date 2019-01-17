#include <iostream>
#include "Patch.h"
#include "GameModel.h"
#include <ctime>

using namespace std;

int main()
{
	cout << "Running patchsim\n";

	// Init RNG used for shuffling
	srand((unsigned)time(0));

	GameModel mdl(2);
	shared_ptr<Patch> p_ref;

#if 0
	while (p_ref = mdl.getNextPatch())
	{
		cout << *p_ref;
	}
#endif
	return 0;
}