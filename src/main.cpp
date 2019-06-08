
#include "GameEngine.hpp"

void get_window_dimensions()
{
	int termy = 0;
	int termx = 0;

	getmaxyx(stdscr, termy, termx);

	std::cout << termy << "/" << termx;
}

int main()
{
	GameEngine engine;
	engine.start();
}
