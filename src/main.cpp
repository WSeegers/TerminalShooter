
#include "GameEngine.hpp"
#include "Body.hpp"

void get_window_dimensions()
{
	int termy = 0;
	int termx = 0;

	getmaxyx(stdscr, termy, termx);

	std::cout << termy << "/" << termx;
}

bool prelaunchTest()
{
	return Body::test();
}

int main()
{
	if (!prelaunchTest())
	{
		return 1;
	}

	GameEngine engine;
	engine.start();
}
