#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <ncurses.h>

class Scoreboard
{
public:
	static const int BOARD_HEIGHT = 50;
	static const int BOARD_WIDTH = 50;

	Scoreboard();
	~Scoreboard();

	void update(int frameCount);

private:
	WINDOW *_board;
};

#endif
