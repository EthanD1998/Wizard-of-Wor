#include "SFML/Graphics.hpp"
#include <iostream>
#include <time.h>
#include <cmath>

#include "pch.h"
#include "StateManager.h"
#include "DisplayState.h"

int main()
{ 
	srand(time(NULL));
	
	StateManager control = StateManager();

	control.init();
}




