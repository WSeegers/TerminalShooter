#include "GameEngine.hpp"

// PlayerEntity makeDefaultPlayer()
// {
// 	std::string l0(" <x> ");
// 	std::string l1("==x=>");
// 	std::string l2(" <x> ");

// 	std::string rawBody = (l0 + l1 + l2);
// 	Body playerBody(rawBody, 5, 3);
// 	return PlayerEntity(Vec2(10, 10), playerBody);
// };

// Projectile makeProjectile()
// {
// 	std::string l0(">");

// 	std::string rawBody = (l0);
// 	Body projBody(rawBody, 1, 1);
// 	return Projectile(Vec2(10, 10), Vec2(0.3, 0), projBody);
// }

bool GameEngine::_didInit = false;

GameEngine::GameEngine() {}

void GameEngine::start(void)
{
	if (this->_running == true)
		return;
	if (!this->_init())
		return;
	this->_running = true;
	while (this->_running)
		this->_mainLoop();
}

GameEngine::~GameEngine() {}

long GameEngine::getFrameCount(void) const
{
	return this->_frameCount;
}

bool GameEngine::_init()
{
	if (GameEngine::_didInit)
		endwin();

	if (COLS < GameEngine::MIN_WIDTH || LINES < GameEngine::MIN_HEIGHT)
	{
		GameEngine::_shutdown();
		std::cout << "Terminal min size is "
							<< GameEngine::MIN_WIDTH << " wide & "
							<< GameEngine::MIN_HEIGHT << " heigh\n";
		return false;
	}
	initscr();
	cbreak();
	noecho();
	timeout(0);
	refresh();
	return true;
}

void GameEngine::_shutdown()
{
	GameEngine::_didInit = false;
	endwin();
}

void GameEngine::_mainLoop(void)
{
	clock_gettime(CLOCK_MONOTONIC, &this->loopStart);

	this->_em.update();

	move(0, 0);

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
