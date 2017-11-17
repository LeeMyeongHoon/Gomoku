#include <cstdio>
#include <cstdlib>
#include "Board.h"
#include <conio.h>

/*****************************************************************************************************************************************/


CheckResult Board::PutStone()
{
	if (IsOverlap())
		return OVERLAP;

	SetDirectionCounts();

	if (IsThreeThree())
		return THREE_THREE;

	data[cursor.x][cursor.y] = curStone;

	if (IsWin())
		return WIN;

	return COUNTIUE;
}


/*****************************************************************************************************************************************/


void Board::PrintBoard() const
{
	std::system("cls");
	for (Location i = 0; i < BOARD_SIZE; i++)
	{
		for (Location j = 0; j < BOARD_SIZE; j++)
		{
			if (cursor.x == i && cursor.y == j)
				PrintCursorStone();
			else
				PrintStone(data[i][j]);
		}
		putchar('\n');
	}
}


/*****************************************************************************************************************************************/


inline void Board::PrintCursorStone() const
{
	if (curStone == BLACK)
	{
		printf("◇");
	}
	else //if(curStone == WHITE)
	{
		printf("◆");
	}
}


/*****************************************************************************************************************************************/


void Board::SelectLocation()
{
	while (true)
	{
		PrintBoard();
		auto input = _getch();
		if (input == NOT_CHAR_KEY)
		{
			input = _getch();
			switch (input)
			{
			case UP:
				if (cursor.x != 0)
					cursor.x--;
				break;
			case DOWN:
				if (cursor.x != BOARD_SIZE - 1)
					cursor.x++;
				break;
			case LEFT:
				if (cursor.y != 0)
					cursor.y--;
				break;
			case RIGHT:
				if (cursor.y != BOARD_SIZE - 1)
					cursor.y++;
				break;
			}
		}
		else if (input == ENTER)
		{
			return;
		}
	}
}


/*****************************************************************************************************************************************/

void PrintStone(const GoStone goStone)
{
	switch (goStone)
	{
	case EMPTY:
		printf("┼");
		break;
	case BLACK:
		printf("○");
		break;
	case WHITE:
		printf("●");
		break;
	}
}


/*****************************************************************************************************************************************/


inline bool Board::IsOverlap() const
{
	return data[cursor.x][cursor.y] != EMPTY;
}


/*****************************************************************************************************************************************/


User Board::GetCurUser() const
{
	return (User)curStone;
}

inline void Board::Reset()
{
	for (Location i = 0; i < BOARD_SIZE; i++)
	{
		for (Location j = 0; j < BOARD_SIZE; j++)
		{
			data[i][j] = EMPTY;
		}
	}
	cursor.x = 0;
	cursor.y = 0;
	curStone = BLACK;
}



/*****************************************************************************************************************************************/


void Board::SwitchUser()
{
	if (curStone == BLACK)
		curStone = WHITE;

	else
		curStone = BLACK;

}


/*****************************************************************************************************************************************/


void Board::SetCursor(const Location i,const Location j)
{
	cursor.x = i;
	cursor.y = j;
}



/*****************************************************************************************************************************************/


inline Direction GetDirectionByOffset(const LocationOffset i_offset, const LocationOffset j_offset)
{
	Direction direction;

	if ((i_offset == -1 && j_offset == -1) || i_offset == +1 && j_offset == +1)
		direction = DIAGONAL1;

	else if ((i_offset == -1 && j_offset == +1) || i_offset == +1 && j_offset == -1)
		direction = DIAGONAL2;

	else if ((i_offset == -1 && j_offset == 0) || i_offset == +1 && j_offset == 0)
		direction = VERTICAL;

	else // if ((i_offset == 0 && j_offset == -1) || i_offset == 0 && j_offset == +1)
		direction = HORIZONTAL;

	return direction;
}


/*****************************************************************************************************************************************/


size_t Board::GetOneDirectionCount(const LocationOffset i_offset, const LocationOffset j_offset)
{
	static size_t bothSide = 0;

	Location i = cursor.x;
	Location j = cursor.y;
	size_t count{};

	i += i_offset;
	j += j_offset;


	while (IsValidRange(i, j) && data[i][j] == curStone)
	{
		count++;
		i += i_offset;
		j += j_offset;
	}

	const Direction direction = GetDirectionByOffset(i_offset, j_offset);
	adjacentStones[direction][bothSide] = data[i][j];
	bothSide = !bothSide; // 양쪽 사이드 교차

	return count;
}


void Board::SetDirectionCounts()
{
	DirectionStoneCounts[HORIZONTAL] = GetOneDirectionCount(0, -1) + GetOneDirectionCount(0, +1) + 1;
	DirectionStoneCounts[VERTICAL] = GetOneDirectionCount(-1, 0) + GetOneDirectionCount(+1, 0) + 1;
	DirectionStoneCounts[DIAGONAL1] = GetOneDirectionCount(-1, -1) + GetOneDirectionCount(+1, +1) + 1; // ↘
	DirectionStoneCounts[DIAGONAL2] = GetOneDirectionCount(+1, -1) + GetOneDirectionCount(-1, +1) + 1; // ↗
}


/*****************************************************************************************************************************************/


Board::Board()
{
	Reset();
}


/*****************************************************************************************************************************************/


bool Board::IsWin() const
{
	return
		DirectionStoneCounts[VERTICAL] == 5 ||
		DirectionStoneCounts[HORIZONTAL] == 5 ||
		DirectionStoneCounts[DIAGONAL1] == 5 ||
		DirectionStoneCounts[DIAGONAL2] == 5;
}


/*****************************************************************************************************************************************/


bool Board::IsThreeThree() const
{
	size_t threeThreeCount{};

	for (size_t direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		if (DirectionStoneCounts[direction] == 3)
		{
			if (adjacentStones[direction][0] == EMPTY && adjacentStones[direction][1] == EMPTY)
			{
				threeThreeCount++;
			}

		}
	}

	return threeThreeCount >= 2;
}


/*****************************************************************************************************************************************/


inline GoStone GetOtherStone(const GoStone goStone)
{
	return goStone == BLACK ? WHITE : BLACK;
}

/*****************************************************************************************************************************************/


inline bool IsValidRange(const Location i, const Location j)
{
	return i >= 0 && j >= 0 && i < BOARD_SIZE && j < BOARD_SIZE;
}

