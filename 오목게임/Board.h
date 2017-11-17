#pragma once
#include <cstdio>
#include "Common.h"

enum KEY
{
	NOT_CHAR_KEY = 224,
	ENTER = 13,
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77
};

enum GoStone
{
	EMPTY,
	BLACK,
	WHITE,
	GO_STONE_COUNT
};

using User = GoStone;

enum Direction
{
	HORIZONTAL,
	VERTICAL,
	DIAGONAL1, // ¢Ù
	DIAGONAL2, // ¢Ö
	DIRECTION_COUNT
};

class Board
{
private:
	GoStone data[BOARD_SIZE][BOARD_SIZE];
	GoStone adjacentStones[DIRECTION_COUNT][2];
	GoStone curStone;
	Location2D cursor;
	size_t DirectionStoneCounts[DIRECTION_COUNT];

	bool IsThreeThree() const;
	bool IsWin() const;

	size_t GetOneDirectionCount(const LocationOffset i_offset, const LocationOffset j_offset);

	void SetDirectionCounts();

	inline bool IsOverlap() const;
	inline void PrintCursorStone() const;
public:
	Board();
	~Board() = default;

	CheckResult PutStone();
	void PrintBoard() const;
	void SelectLocation();

	User GetCurUser() const;
	inline void Reset();
	void SwitchUser();
	void SetCursor(const Location i, const Location j);
};

void PrintStone(const GoStone goStone);

inline bool IsValidRange(const Location i, const Location j);

inline Direction GetDirectionByOffset(const LocationOffset i_offset, const LocationOffset j_offset);

inline GoStone GetOtherStone(const GoStone goStone);


