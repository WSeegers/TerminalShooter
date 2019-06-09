
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

	initscr();
	curs_set(0);
	noecho();
	
	WINDOW *menu = newwin(LINES / 2, COLS / 2, LINES / 4, COLS / 4);
	box(menu, 0, 0);
	refresh();
	wrefresh(menu);
	keypad(menu, true);
	std::string choices[2] = {"START GAME", "   QUIT   "};
	int choice;
	int highlight = 0;

	while (1)
	{
		for (int i = 0; i < 2; i++)
		{
			if (i == highlight)
				wattron(menu, A_REVERSE);
			mvwprintw(menu, (LINES / 4) -1 + i*2, (COLS / 4) - 5, choices[i].c_str());
			wattroff(menu, A_REVERSE);
		}
		choice = wgetch(menu);
		
		switch (choice)
		{
			case KEY_UP:
				highlight--;
				if (highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if (highlight == 2)
					highlight = 1;
				break;
			default:
				break;
		}
		if (choice == 10)
			break;
	}
	if (choices[highlight] == "START GAME")
	{
		wborder(menu, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		wrefresh(menu);
		delwin(menu);
		refresh();
		endwin();
		GameEngine engine;
		engine.start();
	}
	else
	{
		delwin(menu);
		refresh();
		return 0;
	}

}
