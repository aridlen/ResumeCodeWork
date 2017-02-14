#include "stdafx.h"
#include "Enemy.h"
#include "PlayState.h"
#include "Missle.h"
#include"Player.h"
#include"DList.h"
#include "Game.h"
Enemy::Enemy()
{
	SetFG(System::Red);
	SetBG(System::Black);
	SetImage("<-||->");
	SetX(5);
	SetY(3);
	enemymove.resize(2);
	enex = 0;
	eney = 0;

	SetLife(true);

}
Enemy::Enemy(int _x, int _y, System::ConsoleColor _fg, System::ConsoleColor _bg, const char* const _image) : BaseObject(_x, _y, _fg, _bg, _image)
{


}

Enemy::~Enemy()
{
}
Enemy::Enemy(Enemy const& _cpy) : BaseObject(_cpy)
{



}
Enemy& Enemy::operator=(Enemy const& _assign)
{
	if (this != &_assign)
	{
		BaseObject::operator=(_assign);

	}
	return *this;
}
void Enemy::Input(DList<BaseObject*>& _p)
{
	if (player)
	{
		int dx, dy;
		dx = dy = 0;

		if (GetAsyncKeyState('I')) dy = -1;
		if (GetAsyncKeyState('K')) dy = 1;
		if (GetAsyncKeyState('J')) dx = -1;
		if (GetAsyncKeyState('L')) dx = 1;

		if (dx || dy)
		{

			int newx = GetX() + dx;
			int newy = GetY() + dy;

			if (newx >= 0 && newx < System::Console::WindowWidth() - 2 && newy > 0 && newy < System::Console::WindowHeight())
			{
				for (int i = 0; i < 2; ++i)
				{
					if (_p[i] != this)
					{
						if (newx >= _p[i]->GetX() + _p[i]->GetWidth() || newy >= _p[i]->GetY() + _p[i]->GetHeight() || _p[i]->GetX() >= newx + GetWidth() || _p[i]->GetY() >= newy + GetHeight())
						{
							continue;
						}
						else
						{
						
							return;
						}
					}
				}

				SetX(GetX() + dx);


				SetY(GetY() + dy);

				moved = true;
			}
		}
	}
	
	if (GetAsyncKeyState(VK_F9))
	{
		player = true;
		speed = 0;
	}

}
void Enemy::Update(int _frame)
{
	if (!player)
	{
		
		int speedmove = 4;
		if (strcmp(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetDiff(), "Normal") == 0)
		{
			speedmove = 3;
			
		}
		else if (strcmp(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetDiff(), "Hard") == 0)
		{
			speedmove = 2;
			
		}
		
		
		target = PlayState::GetPlayers()[0] ;
			if (_frame % speedmove == 0 && GetLife())
			{
				if (!(Game::GetCheats()&SHOOT_FLAG))
				{
					switch (rand() % 7)
					{
					case 0:
					{
						enemiss = new Missle();
						enemiss->SetVelocity(0, -1);
						enemiss->SetX(GetX() + 2);
						enemiss->SetY(GetY() - 1);
						enemiss->SetLife(true);
						PlayState::GetPlayers().push_back(enemiss);
						break;
					}
					case 1:
					{
						enemiss = new Missle();
						enemiss->SetVelocity(-1, 0);
						enemiss->SetX(GetX() - 1);
						enemiss->SetY(GetY());
						enemiss->SetLife(true);
						PlayState::GetPlayers().push_back(enemiss);
						break;
					}
					case 2:
					{
						enemiss = new Missle();
						enemiss->SetVelocity(1, 0);
						enemiss->SetX(GetX() + 6);
						enemiss->SetY(GetY());
						enemiss->SetLife(true);
						PlayState::GetPlayers().push_back(enemiss);
						break;
					}
					case 3:
					{
						enemiss = new Missle();
						enemiss->SetVelocity(0, 1);
						enemiss->SetX(GetX() + 2);
						enemiss->SetY(GetY() + 1);
						enemiss->SetLife(true);
						PlayState::GetPlayers().push_back(enemiss);
						break;
					}
					default:
					{
#pragma region All directions
						
							enemiss = new Missle();
							enemiss->SetVelocity(0, -1);
							enemiss->SetX(GetX() + 2);
							enemiss->SetY(GetY() - 1);
							enemiss->SetLife(true);
							PlayState::GetPlayers().push_back(enemiss);
						
							enemiss = new Missle();
							enemiss->SetVelocity(-1, 0);
							enemiss->SetX(GetX() - 1);
							enemiss->SetY(GetY());
							enemiss->SetLife(true);
							PlayState::GetPlayers().push_back(enemiss);
						
							enemiss = new Missle();
							enemiss->SetVelocity(1, 0);
							enemiss->SetX(GetX() + 6);
							enemiss->SetY(GetY());
							enemiss->SetLife(true);
							PlayState::GetPlayers().push_back(enemiss);
						
							enemiss = new Missle();
							enemiss->SetVelocity(0, 1);
							enemiss->SetX(GetX() + 2);
							enemiss->SetY(GetY() + 1);
							enemiss->SetLife(true);
							PlayState::GetPlayers().push_back(enemiss);
						
#pragma endregion
						break;
					}
					}
				}
			if (GetLife())
			{
				if (GetY() < target->GetY())
					eney=1;
				else if (GetY() > target->GetY())
					eney = -1;
				else if (GetY() == target->GetY())
					eney = 0;
				if (GetX() < target->GetX())
					enex=1;
				else if (GetX() > target->GetX())
					enex = -1;
				else if (GetX() == target->GetX())
					enex = 0;
			}
			int newx = GetX() + enex;
			int newy = GetY()+eney;
			if (newx > 0 && newx < System::Console::WindowWidth() - 5 && newy > 0 && newy < System::Console::WindowHeight())
			{
				if (!(Game::GetCheats()&MOVE_FLAG))
				{
					for (int i = 0; i < 2; ++i)
					{
						if (PlayState::GetPlayers()[i] != this)
						{
							if (BaseObject::NewCollision(PlayState::GetPlayers()[i], newx, newy))
							{

								continue;
							}
							else
							{
								return;
							}

						}
					}

					if (!(Game::GetCheats()&MOVE_FLAG))
					{
						SetX(newx);
						SetY(newy);
					}
				}

			}
		}
	}

	if (player)
	{
		++speed;

		if (moved)
		{
			speed = 0;
			moved = false;
		}

		if (speed > 200)
			player = false;
	}

}
void Enemy::Render() const
{
	BaseObject::Render();

}