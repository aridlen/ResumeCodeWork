#include "stdafx.h"
#include "Game.h"
#include"BaseObject.h"
#include"Player.h"
#include"Enemy.h"
#include "IBaseState.h"
#include "MenuState.h"
#include "PlayState.h"
#include"HighScores.h"
#include"Game.h"
IBaseState** Game::states = NULL;
IBaseState* Game::currentstate = NULL;

char Game::cheats = 1;
Game::Game()
{
	
	System::Console::EOLWrap(false);
	
	//make temp baseobjects array

	


	states = new IBaseState*[3];

	states[0] = new MenuState();
	states[1] = new PlayState();
	states[2] = new HighScores();
	int i = 0;
	for (; i < MAX_STATES; ++i)
		states[i]->Init();

	currentstate = states[MENU_STATE];
}


Game::~Game()
{
	for (int i = 0; i < MAX_STATES; ++i)
	{

		delete states[i];
	}
	delete[] states;

}
void Game::ChangeState(STATE_IDS _state)
{
	if (_state != 1)
	{
		currentstate->Exit();
	}
	currentstate = states[_state];
	currentstate->Enter();
}
void Game::Play()
{
	System::Console::EOLWrap(false);
	for (; cheats&ALIVE_FLAG&&play; ++frame)
	{
		Input();
		Update(frame);
		Render();

	}
	
	System::Console::EOLWrap(true);
#pragma region Dead Code
#if 0
	BaseObject card(0,2,(System::ConsoleColor)12, (System::ConsoleColor)15, "+---+\n|A  |\n| H |\n|  A|\n+---+"),
		dice(0,8,(System::ConsoleColor)0, (System::ConsoleColor)15, "* *\n * \n* *");
	cout << "Before:\n";
	
	card.Show(); cout << '\n';
	
	dice.Show(); cout << '\n';
	BaseObject temp = card;
	card = dice;
	dice = temp;
	cout << '\n';
	cout << "After:\n";
	card.SetX(0);
	card.SetY(14);
	card.Show(); cout << '\n';
	dice.SetX(0);
	dice.SetY(18);
	dice.Show(); cout << '\n';
	system("pause");
	system("cls");

	BaseObject ship(0,0,(System::ConsoleColor)8, (System::ConsoleColor)0, "|O|");

	int choice;
	for (;;)
	{
		cout << "How many ships do you need Captain? ";
			if (cin >> choice && choice>0)
			{
				cin.sync();
				break;

			}
			cin.clear();
			cin.sync();
	}
	int curry = 1;
	int currx = 0;
	BaseObject* shiptot = new BaseObject[choice];
	for (int i = 0; i < choice; ++i)
	{
		shiptot[i].SetBG(System::Yellow);
		shiptot[i].SetFG(System::Blue);
		
		shiptot[i].SetX(currx*4);
		shiptot[i].SetY(curry);
		shiptot[i].SetImage("|O|");
		if (shiptot[i].GetX() >= System::Console::WindowWidth())
		{
			shiptot[i].SetX(0);
			++curry;
			shiptot[i].SetY(++curry);
			currx = 0;
		}
		currx++;
		shiptot[i].Render();
	}
	cout << '\n';
	system("pause");
	delete[]shiptot;
	BaseObject allobj[3];
	allobj[0] = card;
	allobj[1] = dice;
	allobj[2] = ship;
	
	fstream fout;
	fout.open("savefile.txt", ios_base::out);
		if (fout.is_open())
		{
			fout << 3 << '\n';
			for (int i = 0; i < 3; ++i)
			{
				fout << allobj[i].GetImage() << '\t' << allobj[i].GetBG() << '\t' << allobj[i].GetFB() << endl;
			}

			fout.close();

		}
#endif
#pragma endregion
}
void Game::Input()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		if (currentstate == states[0])
		{

			//cheats ^= 1;
			play = false;
		}
		else
		{
			currentstate->Exit();

			currentstate = states[0];
		}
	}
	if (GetAsyncKeyState(VK_F1)& 0x1)
	{
		//GHOST CHEAT
		
		cheats ^=ALIVE_FLAG;
	}
	if (GetAsyncKeyState(VK_F2) & 0x1)
	{
		//GHOST CHEAT
		
		cheats ^= GHOST_FLAG;
	}
	if (GetAsyncKeyState(VK_F3) & 0x1)
	{
		//MOVE CHEAT
		
		cheats ^= MOVE_FLAG;
	}
	if (GetAsyncKeyState(VK_F4) & 0x1)
	{
		//SHOOT CHEAT
		
		cheats ^= SHOOT_FLAG;
	}
	currentstate->Input();
	
}
void Game::Update(int _Frame)
{
	
	currentstate->Update(_Frame);

}
void Game::Render() const
{
	System::Console::Lock(true);
	System::Console::Clear();

	currentstate->Render();

	System::Console::Lock(false);

	Sleep(10);
}