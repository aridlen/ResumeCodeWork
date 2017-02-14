#include "stdafx.h"
#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "Player.h"
 
MenuState::MenuState()
{
}


MenuState::~MenuState()
{

}

void MenuState::Input()
{
	if (GetAsyncKeyState('W')&&!keypress)
	{
		--menunum;
		if (menunum < 0)
		{
			menunum = 2;
		}
		keypress = true;
	}
	if (GetAsyncKeyState('S')&&!keypress)
	{
		++menunum;

		if (menunum > 2)
			menunum = 0;

		keypress = true;
	}
	if (GetAsyncKeyState(VK_RETURN) && !keypress)
	{
		keypress = true;

		switch (menunum)
		{
		case 0:
		{
			//Switching from menu to the actual game
			Game::ChangeState(PLAY_STATE);
			
			
			break;
		}
		case 1:
		{
			Game::ChangeState(HIGHSCORES_STATE);
			
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		
		}


	}

}
void MenuState::Update(int _frame)
{
	if (!GetAsyncKeyState('W') && !GetAsyncKeyState('S') && !GetAsyncKeyState(VK_RETURN))
	{
		keypress = false;
	}

}
void MenuState::Render()const
{
	
	for (int i = 0; i < 3; ++i)
	{

		if (i == menunum)
		{
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 8, 10 + i);
			cout << "-->";
		}
		else
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 5, 10 + i);

		cout << menuText[i] << '\n';
	}
	System::Console::SetCursorPosition(30, 25);
	cout << "Press ESC to Exit";

}

void MenuState::Enter()
{
	menunum = 0;
}
void MenuState::Exit()
{
	

}

void MenuState::Init()
{
	menunum = 0;
	strcpy_s(menuText[0],128,"Play");
	strcpy_s(menuText[1],128, "Highscores");
	strcpy_s(menuText[2],128,"Options");
	
}
