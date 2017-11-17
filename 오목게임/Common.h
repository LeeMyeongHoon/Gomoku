#pragma once

enum { BOARD_SIZE = 19 };

enum CheckResult
{
	WIN,
	COUNTIUE,
	THREE_THREE,
	OVERLAP
};

using Location = int;
using LocationOffset = int;

struct Location2D
{
	Location x;
	Location y;
};