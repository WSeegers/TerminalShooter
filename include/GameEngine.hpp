#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string>
#include <iostream>

#include "EntityManager.hpp"
#include "Scoreboard.hpp"

#define SEC(s) s * 1000000000

class GameEngine
{
public:
	static const int FIELD_HEIGHT = 80;
	static const int FIELD_WIDTH = 130;
	
	static const int MIN_HEIGHT = GameEngine::FIELD_HEIGHT;
	static const int MIN_WIDTH = GameEngine::FIELD_WIDTH;
	
	static const int FRAME_RATE = 100;
	static const timespec frameTime; // = {0, SEC(1) / FRAME_RATE};

	static const int PLAYER_START_LIVES = 5;

	GameEngine(void);
	~GameEngine(void);
	void start(void);

	long getFrameCount(void) const;
	void stop();

private:
	long _frameCount;
	bool _running;
	bool _didInit;
	WINDOW *_gameField;

	EntityManager _em;

	timespec _loopStart;
	timespec _loopEnd;
	timespec _sleep;
	timespec _diff;

	void _shutdown(void);
	void _mainLoop(void);
	static void drawStaticBorder();

	Scoreboard _scoreboard;
};

/* Util Functions */
timespec diff_ts(const timespec &t1, const timespec &t2);
void printFrameCount(GameEngine &engine);

#endif
