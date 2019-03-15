#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>

#include "Game.h"


int main()
{ 
	srand(time(NULL));
	
	Game game = Game();

	game.init();

}




