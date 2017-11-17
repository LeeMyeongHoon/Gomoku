#pragma once
#include "Board.h"
#include "Common.h"

enum Menu : int
{
	START_GAME,
	EXIT
};


class App
{
private:
	Board board{};
public:
	App() = default;
	~App() = default;

	void Run();
};

Menu PrintMenu();