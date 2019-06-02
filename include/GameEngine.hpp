#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string>

#include "PlayerEntity.hpp"
#include "Body.hpp"

#define SEC(s) s * 1000000000
#define MAX_ENTITES 32

class GameEngine;

typedef void (*UpdateFunc)(GameEngine &engine);

class GameEngine
{
public:
	GameEngine(void);
	const int FRAME_RATE = 60;
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

	PlayerEntity _player;

	timespec loopStart = {0, 0};
	timespec loopEnd = {0, 0};
	timespec sleep = {0, 0};
	timespec diff = {0, 0};

	void _init();
	void _mainLoop(void);

	void _drawBody(int y, int x, const Body &body);
	void _removeBody(int y, int x, const Body &body);
};

/* Util Functions */
timespec diff_ts(const timespec &t1, const timespec &t2);
void printFrameCount(GameEngine &engine);

#endif
