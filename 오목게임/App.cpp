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
				std::cout << "\n�ֻ��� �����Դϴ�.(����Ű�� ���)\n";
				_getch();
				break;
			case OVERLAP:
				std::cout << "\n�̹� �ٵϾ��� �ִ� ���Դϴ�.(�ƹ� ����Ű�� ���)\n";
				_getch();
				break;
			case COUNTIUE:
				board.SwitchUser();
				break;
			}
		}
		board.SetCursor(-1, -1);  // Ŀ�� ��� ����
		board.PrintBoard();
		std::cout << '\n' << userNames[winner] << "�¸�\n(�ƹ� ����Ű�� ���)\n";
		_getch();
	}
}

Menu PrintMenu()
{
	std::system("cls");
	std::cout << "�̸����� ��������Դϴ�.\n";
	std::cout << '[' << Menu::START_GAME << "] ���ӽ���\n";
	std::cout << '[' << Menu::EXIT << "] ���α׷� ����\n\n";

	std::cout << "���Ͻô� �޴��� �Է����ּ��� : ";

	int inputKey;
	while (true)
	{
		std::cin >> inputKey;
		if (inputKey != START_GAME && inputKey != EXIT)
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ��� : ";
		else
			return (Menu)inputKey;
	}
}