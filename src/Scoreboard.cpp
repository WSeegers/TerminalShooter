#include "Scoreboard.hpp"
#include "GameEngine.hpp"

static WINDOW *createBoard()
{
	WINDOW *subwindow = newwin(Scoreboard::BOARD_WIDTH, Scoreboard::BOARD_HEIGHT, 0, GameEngine::FIELD_WIDTH);
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

void Scoreboard::update(int frameCount)
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

void Scoreboard::setScore(int i)
{
	this->_score = i;
}

void Scoreboard::setLives(int i)
{
	this->_lives = i;
}

void Scoreboard::incScore(int i)
{
	this->_score += i;
}

void Scoreboard::decScore(int i)
{
	this->_score -= i;
}

void Scoreboard::incLives(int i)
{
	this->_score += i;
}

void Scoreboard::decLives(int i)
{
	this->_score -= i;
}

int Scoreboard::_getTime()
{
	return (std::time(nullptr) - this->_startTime);
}
