// Ovde ukljuciti Vase fajlove
#include "tst.h"
#include "game.h"
#include <iostream>
using namespace std;

// forward declare tested types
class Game;

int main(int argc, char const* argv[]) {
	using namespace std;
	int pts = 0;

	// This test simulates the game
	pts += Test0::tst<Game>();
	pts += Test1::tst<Game>();
	pts += Test2::tst<Game>();
	pts += Test3::tst<Game>();
	pts += Test4::tst<Game>();


	std::cout << "Points: " << pts << std::endl;

	return 0;
}
