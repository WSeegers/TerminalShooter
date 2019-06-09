#include "Scoreboard.hpp"
#include "GameEngine.hpp"

static WINDOW *createBoard()
{
	WINDOW *subwindow = newwin(GameEngine::FIELD_HEIGHT, Scoreboard::BOARD_WIDTH, 0, GameEngine::FIELD_WIDTH);
	box(subwindow, 0, 0);

	return subwindow;
}

Scoreboard::Scoreboard() : _board(createBoard()), _score(0), _lives(0)
{
	this->_startTime = std::time(nullptr);

	mvprintw(2, GameEngine::FIELD_WIDTH + 5, "===============SCOREBOARD===============");
	wrefresh(this->_board);
}

Scoreboard::Scoreboard(int lives) : _board(createBoard()), _score(0), _lives(lives)
{
	this->_startTime = std::time(nullptr);

	mvprintw(2, GameEngine::FIELD_WIDTH + 5, "===============SCOREBOARD===============");
	wrefresh(this->_board);
}

Scoreboard::~Scoreboard()
{
	delwin(this->_board);
}

void Scoreboard::update()
{
	int startColumn = GameEngine::FIELD_WIDTH + 5;
	int startRow = 5;

	mvprintw(startRow, startColumn, "TIME:  ");
	mvprintw(startRow, startColumn + 8, std::to_string(this->_getTime()).c_str());
	mvprintw(startRow + 1, startColumn, "SCORE: ");
	mvprintw(startRow + 1, startColumn + 8, std::to_string(this->_score).c_str());
	mvprintw(startRow + 2, startColumn, "LIVES: ");
	mvprintw(startRow + 2, startColumn + 8, std::to_string(this->_lives).c_str());

	wrefresh(this->_board);
}

int Scoreboard::getScore()
{
	return (this->_score);
}

uint32_t Scoreboard::getLives()
{
	return (this->_lives);
}

void Scoreboard::setScore(int i)
{
	this->_score = i;
}

void Scoreboard::setLives(uint32_t i)
{
	this->_lives = i;
}

void Scoreboard::incScore(uint32_t i)
{
	this->_score += i;
}

void Scoreboard::decScore(uint32_t i)
{
	this->_score -= i;
}

void Scoreboard::incLives(uint32_t i)
{
	this->_lives += i;
}

void Scoreboard::decLives(uint32_t i)
{
	if (((int)this->_lives - (int)i) < 0)
	{
		this->_lives = 0;
	}
	else
	{
		this->_lives -= i;
	}
}

int Scoreboard::_getTime()
{
	return (std::time(nullptr) - this->_startTime);
}
