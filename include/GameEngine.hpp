#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string>
#include <signal.h>
#include <iostream>

#include "EntityManager.hpp"

#define SEC(s) s * 1000000000
#define MAX_ENTITES 32

class GameEngine;

typedef void (*UpdateFunc)(GameEngine &engine);

class GameEngine
{
public:

	static const int MIN_HEIGHT = 50;
	static const int MIN_WIDTH = 100;
	static const int FIELD_HEIGHT = 50;
	static const int FIELD_WIDTH = 100;
	static const int FRAME_RATE = 100;
	static const timespec frameTime; // = {0, SEC(1) / FRAME_RATE};

	GameEngine(void);
	// GameEngine(const UpdateFunc updateFunc);
	~GameEngine(void);
	void start(void);

	long getFrameCount(void) const;
	// void setUpdateFunction(const UpdateFunc updateFunc);
	void stop();

private:
	bool _running = false;
	long _frameCount = 0;
	UpdateFunc _updateFunc;

	EntityManager _em;

	timespec loopStart = {0, 0};
	timespec loopEnd = {0, 0};
	timespec sleep = {0, 0};
	timespec diff = {0, 0};

	static bool _didInit;
	static bool _init(void);
	static void _shutdown(void);
	void _mainLoop(void);
	static void drawStaticBorder();
};

/* Util Functions */
timespec diff_ts(const timespec &t1, const timespec &t2);
void printFrameCount(GameEngine &engine);

#endif
