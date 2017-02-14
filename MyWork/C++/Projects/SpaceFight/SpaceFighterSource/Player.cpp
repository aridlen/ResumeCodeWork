#include "stdafx.h"
#include "Player.h"
#include "Missle.h"
#include "PlayState.h"
#include"DList.h"
#include "Game.h"
Player::Player()
{
	//name = NULL;
}

Player::Player(int _x, int _y, int _score, string _diff, const char* const _name, System::ConsoleColor _fg, System::ConsoleColor _bg, const char* const _image) : BaseObject(_x, _y, _fg, _bg, _image)
{
	//name = NULL;
	
	SetScore(_score);
	SetDiff(_diff);
	
	SetLP(100);
	SetName(_name);

}


Player::~Player()
{
	//delete[]name;
}



void Player::Input(DList<BaseObject*>& _p)
{
	int dx, dy;
	dx = dy = 0;
	if (GetAsyncKeyState('W'))dy = -1;
	if (GetAsyncKeyState('S'))dy = 1;
	if (GetAsyncKeyState('A'))dx = -1;
	if (GetAsyncKeyState('D'))dx = 1;

	if (dx || dy)
	{
		int newx = GetX() + dx;
		int newy = GetY() + dy;

		if (newx + 1 > 1 && newx + GetWidth() < System::Console::WindowWidth()  && newy > 1 && newy + GetHeight() < System::Console::WindowHeight() + 3)
		{

		
			if (!(Game::GetCheats()&GHOST_FLAG))
			{
				for (int i = 0; i < 2; ++i)
				{
					if (_p[i] != this)
					{
						if (BaseObject::NewCollision(_p[i],newx,newy))
						{
							continue;
						}
						else
						{
							
							return;
						}
					}
				}
				}

				SetX(newx);
				SetY(newy);
		}
	}
	
	if (GetAsyncKeyState(VK_UP))
	{
		Missle* m = new Missle();
		m->SetVelocity(0, -1);
		m->SetX(GetX()+2);
		m->SetY(GetY()-1);
		m->SetLife(true);
		
		PlayState::GetPlayers().push_back(m);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		Missle* m = new Missle();
		m->SetVelocity(-1, 0);
		m->SetX(GetX() - 1);
		m->SetY(GetY());
		m->SetLife(true);
		PlayState::GetPlayers().push_back(m);

	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		Missle* m = new Missle();
		m->SetVelocity(1, 0);
		m->SetX(GetX() + 5);
		m->SetY(GetY());
		m->SetLife(true);
		PlayState::GetPlayers().push_back(m);

	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		Missle* m = new Missle();
		m->SetVelocity(0, 1);
		m->SetX(GetX()+2);
		m->SetY(GetY()+1);
		m->SetLife(true);
		PlayState::GetPlayers().push_back(m);

	}
}
void Player::Update(int _frame)
{


}
void Player::Render()const
{
	System::Console::SetCursorPosition(0, 0);
	System::Console::ForegroundColor(System::White);
	cout << "Name: " << name.c_str();

	System::Console::SetCursorPosition((System::Console::WindowWidth()>>1)-18, 0);
	System::Console::ForegroundColor(System::Yellow);
	cout << "Score: " << score;

	System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 3, 0);
	System::Console::ForegroundColor(System::White);
	cout << "LIFE ";
	if (lifepoints>60)
	System::Console::BackgroundColor(System::Green);
	else if (lifepoints<=60 && lifepoints>30)
	System::Console::BackgroundColor(System::Yellow);
	else
	{
		System::Console::BackgroundColor(System::Red);
		
	}
	cout << lifed.c_str();
	System::Console::ResetColor();
	System::Console::ForegroundColor(System::White);
	if (lifepoints <= 0)
		cout << " " << 0 << "%";
	else
	cout << " "<<lifepoints<<"%";

	System::Console::SetCursorPosition(System::Console::WindowWidth()-19, 0);
	System::Console::ForegroundColor(System::White);
	
	cout << "Difficulty: " << difficulty.c_str();
	System::Console::ResetColor();
	BaseObject::Render();

}
Player::Player(Player const& _cpy) : BaseObject(_cpy)
{
	//name = NULL;
	SetScore(_cpy.score);
	SetDiff(_cpy.difficulty);
	SetName(_cpy.name.c_str());

}
Player& Player::operator=(Player const& _assign)
{
	if (this != &_assign)
	{
		BaseObject::operator=(_assign);
		SetScore(_assign.score);
		SetDiff(_assign.difficulty);
		SetName(_assign.name.c_str());

	}
	return *this;
}