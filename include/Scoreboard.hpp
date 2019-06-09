#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <ncurses.h>
#include <string>
#include <ctime>

class Scoreboard
{
public:
	static const int BOARD_WIDTH = 50;

	Scoreboard();
	Scoreboard(int lives);
	~Scoreboard();

	void update();

	void setScore(int i);
	void setLives(int i);

	void incScore(int i);
	void decScore(int i);
	void incLives(int i);
	void decLives(int i);

private:
	WINDOW *_board;

	uint32_t _score;
	uint32_t _lives;

	std::time_t _startTime;
	int _getTime();
};

#endif
