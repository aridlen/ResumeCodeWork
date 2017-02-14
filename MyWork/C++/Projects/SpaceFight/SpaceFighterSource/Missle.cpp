#include "stdafx.h"
#include "Missle.h"
#include "Player.h"
#include "PlayState.h"
#include"DList.h"
#include "Game.h"
Missle::Missle()
{
	int randcolor = rand() % 4;
	switch (randcolor)
	{
	case 0:
		SetFG((System::Blue));
		break;
	case 1:
		SetFG((System::Yellow));
		break;
	case 2:
		SetFG((System::Red));
		break;
	case 3:
		SetFG((System::Green));
		break;
	}
	
	SetBG(System::Black);
	SetImage("*");
	
	velVec.resize(2);
	velX = 0;
	VelY = 0;
	SetLife(true);
	

}


Missle::~Missle()
{
}

void Missle::Input(DList<BaseObject*>& _p)
{

}
void Missle::Update(int _frame)
{
	
	if (GetLife()&&_frame%1==0)
	{
		
		int newx = GetX() + velX;
		int newy = GetY() + VelY;
	
		if (newx + 1 > 0 && newx + GetWidth() < System::Console::WindowWidth() + 1 && newy > 0 && newy + GetHeight() < System::Console::WindowHeight() + 1)
		{


			if (!(Game::GetCheats()&GHOST_FLAG))
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
							SetLife(false);

							//delete _p[i];
							//_p.erase(_p.begin()+i--);
							if (dynamic_cast<Player*>(PlayState::GetPlayers()[i]))
							{
								if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP()<=0)
									dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLP(0);
								if (strcmp(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetDiff(),"Normal")==0)
									dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLP(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() - 13);
								else if (strcmp(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetDiff(), "Hard")==0)
									dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLP(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() - 18);
								else
								dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLP(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() - 6);

								RenderingLife();
							}
							else
								dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetScore(dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetScore() + 10);
							return;
						}
					}
				}
			}

			SetX(newx);
			SetY(newy);
		}
		else
			SetLife(false);

	}
}
void Missle::Render() const
{
	if (GetLife())
	{
		BaseObject::Render();
	}
}
void Missle::RenderingLife()
{
	
	if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 90 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 80)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("         ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 80 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 70)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("        ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 70 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 60)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("       ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 60 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 50)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("      ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 50 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 40)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("     ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 40 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 30)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("    ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 30 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 20)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("   ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 20 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 10)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("  ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() < 10 && dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() > 0)
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD(" ");
	else if (dynamic_cast<Player*>(PlayState::GetPlayers()[0])->GetLP() <= 0)
	{
		
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetLD("DEAD");
		
	}
}