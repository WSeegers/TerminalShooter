#include "Scoreboard.hpp"
#include "GameEngine.hpp"

static WINDOW *createBoard()
{
	WINDOW *subwindow = newwin(Scoreboard::BOARD_WIDTH, Scoreboard::BOARD_HEIGHT, 0, GameEngine::FIELD_WIDTH);
	box(subwindow, 0, 0);

	return subwindow;
}

Scoreboard::Scoreboard() : _board(createBoard()) {}

Scoreboard::~Scoreboard()
{
	delwin(this->_board);
}

void Scoreboard::update(int frameCount)
{
	wrefresh(this->_board);
}
