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

	void update(int frameCount);

	int getScore();
	uint32_t getLives();
	void setScore(int i);
	void setLives(uint32_t i);

	void incScore(uint32_t i);
	void decScore(uint32_t i);
	void incLives(uint32_t i);
	void decLives(uint32_t i);

private:
	WINDOW *_board;

	int _score;
	uint32_t _lives;

	std::time_t _startTime;
	int _getTime();
};

#endif
