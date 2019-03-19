#include "SFML/Graphics.hpp"
#include <iostream>
#include <time.h>
#include <cmath>

#include "StateManager.h"
//#include "StateManager.cpp"

#include "DisplayState.h"
//#include "DisplayState.cpp"

int main()
{ 
	srand(time(NULL));
	
	StateManager control = StateManager();

	control.init();
}