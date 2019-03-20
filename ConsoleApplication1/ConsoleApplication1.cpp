#include "pch.h"
#include "StateManager.h"

/*
	Main() is small on purpose.
	StateManager will handle everything, instead of main() being messy.
*/
int main()
{ 	
	srand(time(NULL));
	StateManager control = StateManager();
	control.init();
}
