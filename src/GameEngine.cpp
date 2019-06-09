#include "GameEngine.hpp"

const timespec GameEngine::frameTime = {0, SEC(1) / GameEngine::FRAME_RATE};

static bool _init()
{
	initscr();
	// TODO need to be handled better
	if (COLS < GameEngine::MIN_WIDTH || LINES < GameEngine::MIN_HEIGHT)
	{
		std::cout << "Terminal min size is "
				  << GameEngine::MIN_WIDTH << " wide & "
				  << GameEngine::MIN_HEIGHT << " heigh\n";
		return false;
	}
	cbreak();
	noecho();
	curs_set(0);
	timeout(0);
	refresh();
	return true;
}

static WINDOW *createGameField()
{
	WINDOW *subwindow = newwin(GameEngine::FIELD_HEIGHT, GameEngine::FIELD_WIDTH, 0, 0);
	box(subwindow, 0, 0);

	return subwindow;
}

GameEngine::GameEngine() : _didInit(_init()), _gameField(createGameField()), _em(this->_gameField)
{
}

void GameEngine::start(void)
{
	if (this->_running == true)
		return;
	if (!this->_didInit)	
		return;
	this->_running = true;
	while (this->_running)
		this->_mainLoop();
}

void GameEngine::drawStaticBorder()
{
	int width = GameEngine::FIELD_WIDTH;
	int height = GameEngine::FIELD_HEIGHT;
	for (int y = 0; y <= height; y++)
	{
		for (int x = 0; x <= width; x++)
		{
			if (x == 0 || y == height || x == width || y == 0)
				mvaddch(y, x, '#');
		}
	}
}

GameEngine::~GameEngine() {}

long GameEngine::getFrameCount(void) const
{
	return this->_frameCount;
}

void GameEngine::_shutdown()
{
	this->_didInit = false;
	delwin(this->_gameField);
	endwin();
}

void GameEngine::_mainLoop(void)
{
	clock_gettime(CLOCK_MONOTONIC, &this->loopStart);

	this->_em.update(this->_frameCount);

	clock_gettime(CLOCK_MONOTONIC, &this->loopEnd);
	this->diff = diff_ts(loopEnd, loopStart);
	this->sleep = diff_ts(diff, frameTime);
	if (!sleep.tv_sec && sleep.tv_nsec < SEC(1) / GameEngine::FRAME_RATE)
		nanosleep(&sleep, NULL);
	this->_frameCount++;
}

void GameEngine::stop()
{
	this->_running = false;
}

/* Util Functions */
timespec diff_ts(const timespec &t1, const timespec &t2)
{
	int sec = std::abs(t1.tv_sec - t2.tv_sec);
	int nano = std::abs(t1.tv_nsec - t2.tv_nsec);
	timespec ret;
	ret.tv_sec = sec + nano - (nano % 1000000000);
	ret.tv_nsec = nano % 1000000000;

	return ret;
}

// Debug function to print out game frames
void printFrameCount(GameEngine &engine)
{
	printw("           ");
	move(0, 1);
	printw("#%ld", engine.getFrameCount() / 60);
	move(1, 1);
	printw("#%ld", engine.getFrameCount());
}
