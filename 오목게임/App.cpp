#include <cstdlib>
#include <iostream>
#include <conio.h>
#include "App.h"
//
static const char* userNames[GO_STONE_COUNT] = { "","BLACK","WHITE" };

void App::Run()
{
	while (START_GAME == PrintMenu())
	{
		board.Reset();
		User winner = EMPTY;
		while (!winner)
		{
			board.SelectLocation();
			auto putResult = board.PutStone();
			switch (putResult)
			{
			case WIN:
				winner = board.GetCurUser();
				break;
			case THREE_THREE:
				std::cout << "\n쌍삼은 금지입니다.(문자키로 계속)\n";
				_getch();
				break;
			case OVERLAP:
				std::cout << "\n이미 바둑알이 있는 곳입니다.(아무 문자키로 계속)\n";
				_getch();
				break;
			case COUNTIUE:
				board.SwitchUser();
				break;
			}
		}
		board.SetCursor(-1, -1);  // 커서 출력 방지
		board.PrintBoard();
		std::cout << '\n' << userNames[winner] << "승리\n(아무 문자키로 계속)\n";
		_getch();
	}
}

Menu PrintMenu()
{
	std::system("cls");
	std::cout << "이명훈의 오목게임입니다.\n";
	std::cout << '[' << Menu::START_GAME << "] 게임시작\n";
	std::cout << '[' << Menu::EXIT << "] 프로그램 종료\n\n";

	std::cout << "원하시는 메뉴를 입력해주세요 : ";

	int inputKey;
	while (true)
	{
		std::cin >> inputKey;
		if (inputKey != START_GAME && inputKey != EXIT)
			std::cout << "잘못된 입력입니다. 다시 입력하세요 : ";
		else
			return (Menu)inputKey;
	}
}