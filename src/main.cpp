#include <iostream>
#include <string>
#include <ncurses.h>
#include <signal.h>
#include <GameEngine.hpp>

#define FRAME_RATE 1000000000 / 30

void terminal_start()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	refresh();
}

void terminal_stop()
{
	endwin();
}

void terminal_exit()
{
	std::cout << "Press any key to exit..." << std::endl;
	getch();
	endwin();
};

void get_window_dimensions()
{
	int termy = 0;
	int termx = 0;

	getmaxyx(stdscr, termy, termx);

	std::cout << termy << "/" << termx;
}

void resizehandler(int sig)
{

	terminal_stop();
	terminal_start();

	get_window_dimensions();

	// draw_window(mapwin, mapwiny, mapwinx, 'm');
	// draw_window(sidebar, sidebary, sidebarx, 's');
}

void test(int sig)
{
	std::cout << "resize ";
}

void update(GameEngine &engine)
{
	printw("           ");
	move(0, 0);
	printw("#%ld", engine.getFrameCount() / 60);
	move(1, 0);
	printw("#%ld", engine.getFrameCount());
	refresh();
	if (engine.getFrameCount() > 9999999)
		engine.stop();
}

int main()
{
	GameEngine engine;
	engine.start();
}
