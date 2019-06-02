#include "GameEngine.hpp"

PlayerEntity makeDefaultPlayer()
{
	std::string l0(" <x> ");
	std::string l1("==x=>");
	std::string l2(" <x> ");

	std::string rawBody = (l0 + l1 + l2);
	Body playerBody(rawBody, 5, 3);
	return PlayerEntity(playerBody);
};

GameEngine::GameEngine() : _player(makeDefaultPlayer()){};

void GameEngine::start(void)
{
	if (this->_running == true)
		return;
	this->_init();
	this->_running = true;
	while (this->_running)
		this->_mainLoop();
}

GameEngine::~GameEngine() {}

long GameEngine::getFrameCount(void) const
{
	return this->_frameCount;
}

void GameEngine::_init()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	timeout(0);
	refresh();
}

void GameEngine::_mainLoop(void)
{
	clock_gettime(CLOCK_MONOTONIC, &this->loopStart);

	// Temp Player movements
	char c = getch();
	switch (c)
	{
	case 'w':
		this->_player.moveUP();
		break;
	case 'a':
		this->_player.moveLEFT();
		break;
	case 's':
		this->_player.moveDOWN();
		break;
	case 'd':
		this->_player.moveRIGHT();
		break;
	}

	if (c > -1)
	{
		mvprintw(0, 1, "X: %f", this->_player.getPosition().x);
		mvprintw(1, 1, "Y: %f", this->_player.getPosition().y);
	}

	this->_drawBody(this->_player.getPosition().y,
									this->_player.getPosition().x,
									this->_player);

	move(0, 0);
	refresh();
	this->_removeBody(this->_player.getPosition().y,
										this->_player.getPosition().x,
										this->_player);

	clock_gettime(CLOCK_MONOTONIC, &this->loopEnd);
	this->diff = diff_ts(loopEnd, loopStart);
	this->sleep = diff_ts(diff, {0, SEC(1) / FRAME_RATE});
	if (!sleep.tv_sec && sleep.tv_nsec < SEC(1) / FRAME_RATE)
		nanosleep(&sleep, NULL);
	this->_frameCount++;
}

void GameEngine::stop()
{
	this->_running = false;
}

void GameEngine::_drawBody(int y, int x, const Body &body)
{
	int _cy = -1;
	int _cx;

	int width = body.getWidth();
	int height = body.getHeight();
	const std::string &_body = body.getBody();

	while (++_cy < height)
	{
		_cx = -1;
		while (++_cx < width)
		{
			// Todo: add handle for "blank val"
			mvaddch(
					_cy + y,
					_cx + x,
					_body[_cx + _cy * width]);
		}
	}
}

void GameEngine::_removeBody(int y, int x, const Body &body)
{
	int _cy = -1;
	int _cx;

	int width = body.getWidth();
	int height = body.getHeight();

	while (++_cy < height)
	{
		_cx = -1;
		while (++_cx < width)
		{
			mvaddch(
					_cy + y,
					_cx + x,
					' ');
		}
	}
}

/* Util Functions */
timespec diff_ts(const timespec &t1, const timespec &t2)
{
	int sec = std::abs(t1.tv_sec - t2.tv_sec);
	int nano = std::abs(t1.tv_nsec - t2.tv_nsec);
	return {sec + nano - nano % 1000000000, nano % 1000000000};
}

void printFrameCount(GameEngine &engine)
{
	printw("           ");
	move(0, 0);
	printw("#%ld", engine.getFrameCount() / 60);
	move(1, 0);
	printw("#%ld", engine.getFrameCount());
}
