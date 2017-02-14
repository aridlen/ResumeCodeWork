#include "stdafx.h"
#include "PlayState.h"

#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Missle.h"
#include "HighScores.h"
#include"DList.h"
DList<BaseObject*> PlayState::players;
vector<PlayInfo>HighScores::final_scores;
PlayState::PlayState()
{
}


PlayState::~PlayState()
{
	decltype(players.size())i = 0;
	for (; i < players.size(); ++i)
	{
		delete players[i];
	}
	delete[]cellimage;
}
void PlayState::Input()
{
	decltype(players.size())i = 0;
	for (; i < players.size(); ++i)
	{
	 players[i]->Input(players);
	}
}
void PlayState::Update(int _frame)
{
	decltype(players.size())i = 0;
	for (; i < players.size(); ++i)
	{
		players[i]->Update(_frame);
#pragma region Iterator notes
		// check if players[i]
		// missile* m = dynamic cast players[i]
		// if (m)
		//{
		// if m is dead
		// {
		// delete [i] from vector
		// erase
		// }
		//}
		//Missle* m;

		/*
		vector<int>::iterator intvector;
		1	2	3
		^
		iter=intvector.begin();
		cout<<*iter<<endl;  -must dereference
		++iter -moves the place in container
		[1]	[2]	[3]
			 ^
			 while(iter!=intvector.end())
			 ++iter
		*/
#pragma endregion		
		if (dynamic_cast<Missle*>(players[i]))
		{
			if (players[i]->GetLife() == false)
			{
				delete players[i];
				players.erase(i--);
			}
		}
		
	}
	if (dynamic_cast<Player*>(players[0])->GetLP() <= 0)
	{
		dynamic_cast<Player*>(players[0])->Render();
		Sleep(2000);
		Game::SetCheats(1);
		dynamic_cast<Player*>(players[0])->SetLP(100);
		Game::ChangeState(MENU_STATE);
	}
}
void PlayState::Render()const
{
	int colorrand = rand() % 12;
	System::Console::ForegroundColor(colorrand);
	System::Console::DrawBox(0, 1, System::Console::WindowWidth(), System::Console::WindowHeight()-2,true);
	for(int i=0;i<cellsize;++i)
	{
		cellimage[i].Show(0,0);
	}
	/*System::Console::SetCursorPosition(3, System::Console::WindowHeight() - 1);
	for(int i=7;i>=0;--i)
	{
		cout<<((Game::GetCheats()>>i)&1);
	}*/
	System::Console::SetCursorPosition(0, System::Console::WindowHeight() - 1);
	cout<<"   F1 = Nuke Game   "<<"F2 = Ghost Mode   "<<"F3 = Freeze Enemy   "<<"F4 = No Shooting";

#pragma region Actual Players Render
#if 0
	for (int i = 0; i < 2; ++i)
	{
		players[i]->Render();

	}
#endif
#pragma endregion
#pragma region istream Render
#if 1
	decltype(players.size())i = 0;
	for (; i < players.size(); ++i)
	{
		players[i]->Render();

	}
#endif
#pragma endregion
}

void PlayState::Enter()
{
#pragma region Text Readin
#if 0
	readin = true;
	char buffer[16];
	int scorebuff;
	char diffbuff[7];
	ifstream fin;
	fin.open("savefilePlayer.txt");
	if (fin.is_open())
	{
		
		fin.close();

	}
	
#endif
#pragma endregion

	system("cls");
	Game::SetCheats(1);
	cout << "Rules:" << endl;
	cout << "You are the blue icon." << endl;
	cout << "To move use: " << endl;
	cout << " W " << endl;
	cout << "A D" << endl;
	cout << " S " << endl;
	cout << "Use arrow keys to shoot." << endl;
	cout << "If you hit the enemy you gain 10 points." << endl;
	cout << "If the enemy hits you, you will lose health." << endl;
	cout << "Press ESC at anytime to exit back to menu." << endl;
	system("pause");
	if (!readin)
	{
		system("cls");
		int spaces = 0;
		char username[16] = { "Default" };
		for (;;)
		{
			cout << "Enter player name: ";
			if (cin.get(username, 16) && cin.good())
			{
				cin.sync();
				for (unsigned int i = 0;i<= strlen(username); ++i)
				{
					if (username[i] == ' ')
					{
						++spaces;
					}
					if (spaces > 2)
					{
						strcpy_s(username, 16, "Default");
						cout << "Too many spaces! You have been set to Default." << endl;
						break;
					}
				}
				break;

			}

			cin.clear();
			cin.ignore();
			/*system("cls");
			cout << "Name was not accepted. Please try again.";
			Sleep(1000);*/
			system("cls");

		}
		dynamic_cast<Player*>(PlayState::GetPlayers()[0])->SetName(username);
		int diffchoice;
		for (;;)
		{
			cout << "1) Easy" << endl;
			cout << "2) Normal" << endl;
			cout << "3) Hard" << endl;
			if (cin >> diffchoice && diffchoice > 0 && diffchoice < 4)
			{
				cin.sync();
				break;

			}

			cin.clear();
			cin.ignore();
			system("cls");

		}
		switch (diffchoice)
		{
		case 1:
		{
			dynamic_cast<Player*>(GetPlayers()[0])->SetDiff("Easy");
			
			break;
		}
		case 2:
		{
			dynamic_cast<Player*>(GetPlayers()[0])->SetDiff("Normal");
			
			break;
		}
		case 3:
		{
			dynamic_cast<Player*>(GetPlayers()[0])->SetDiff("Hard");
			break;
		}
		}
	}
}
void PlayState::Exit()
{
	system("cls");
	System::Console::SetCursorPosition(32,10);
	cout << "Game Over!" << endl;
	Sleep(1000);
	system("cls");
	System::Console::SetCursorPosition(32, 10);
	Player* player1 = dynamic_cast<Player*>(players[0]);
	if (player1)
	{
		cout <<player1->GetName() <<"'s Score: " << player1->GetScore()<<endl;
		System::Console::SetCursorPosition(32, 11);
		cout << player1->GetName() << "'s Difficulty: " << player1->GetDiff() << endl;
		System::Console::SetCursorPosition(0,System::Console::WindowHeight() );
		system("pause");
	}
	system("cls");
	
#pragma region Save text
#if 0
	
	char filename[32];
	for (;;)
	{
		cout << "Name the text file: " << endl;
		if (cin.good() && cin.get(filename, 32))
		{
			cin.sync();
			break;
		}
		cin.clear();
		cin.ignore();
		system("cls");
	}
	fstream fout;
	fout.open(filename, ios_base::out);
	if (fout.is_open())
	{


		fout << dynamic_cast<Player*>(players[0])->GetName() << '\t' << dynamic_cast<Player*>(players[0])->GetScore() << '\t' << dynamic_cast<Player*>(players[0])->GetDiff() << '\n';
		
		fout.close();
	}
	
#endif
#pragma endregion
#pragma region Binary Save output single
#if 1
	
		PlayInfo PLAY1_INFO;
		//vector<PlayInfo> final_scores;

		strcpy_s(PLAY1_INFO.name, 16, player1->GetName());
		PLAY1_INFO.score = player1->GetScore();
		strcpy_s(PLAY1_INFO.diff, 8, player1->GetDiff());
		//Clear here
		HighScores::GetHighScores().clear();
		HighScores::GetHighScores().push_back(PLAY1_INFO);
		vector<PlayInfo>& temp = HighScores::GetHighScores();

		fstream bout;
		bout.open("scores.bin", ios_base::binary | ios_base::out | ios_base::app);
		if (bout.is_open())
		{
			//bout.write((char*)&PLAY1_INFO, sizeof(PlayInfo));
			bout.write((char*)&HighScores::GetHighScores()[0], sizeof(PlayInfo)*HighScores::GetHighScores().size());
			bout.close();
		}
	
#endif
#pragma endregion
	
#pragma region Binary READIN Loop
#if 0
	fstream bin;
	bin.open("scores.bin", ios_base::binary | ios_base::in);
	if (bin.is_open())
	{
		bin.seekg(0, ios_base::end);
		int count = (int)bin.tellg();
		count /= sizeof(PlayInfo);

		bin.seekg(0, ios_base::beg);
		final_scores.resize(count);
		for (int i = 0; i < count; ++i)
		{
			bin.read((char*)&final_scores[i], sizeof(PlayInfo));
		}
		bin.close();
	}
#endif
#pragma endregion
#pragma region bin READIN single
#if 0
	fstream bin;
	bin.open("scores.bin", ios_base::binary | ios_base::in);
	if (bin.is_open())
	{
		bin.seekg(0, ios_base::end);
		int count = (int)bin.tellg();
		count /= sizeof(PlayInfo);
		
		bin.seekg(0, ios_base::beg);
		final_scores.resize(count);
		bin.read((char*)&final_scores[0], sizeof(PlayInfo));
		bin.close();
	}


#endif
#pragma endregion
}

void PlayState::Init()
{
	
	cellsize = 20;
	if (cellsize % 2)
	{
		++cellsize;
	}
	cellimage = new Cell<int, char>[cellsize];
	for (int i = 0; i < cellsize; ++i)
	{
		cellimage[i].SetOX(rand() % System::Console::WindowWidth());
		cellimage[i].SetOY(rand() % System::Console::WindowHeight());
		for (int j = 0; j < i; ++j)
		{
			if (cellimage[i].GetX() == cellimage[j].GetX() && cellimage[i].GetY() == cellimage[j].GetY())
			{
				--i;
				break;
			}
		}


	}
	for (int i = 0; i < cellsize; ++i)
	{
		int mix = rand() % 2;
		if (mix == 0)
		{
			cellimage[i].SetFG(System::White);
		}
		else
		{
			cellimage[i].SetFG(System::Gray);
		}
		cellimage[i].SetBG(System::Black);
		if (mix == 0)
		{
			cellimage[i].SetSYM('*');
		}
		else
		{
			cellimage[i].SetSYM('o');
		}
		

	}

#pragma region ActualPlayers
#if 1
	//players = new BaseObject*[2];
	//players.resize(2);
	BaseObject* temp = new Player(15, 15, 0, "Normal", "Default", System::Blue, System::Black, "_/T\\_");
	players.push_back(temp);
	//players[0] = new Player(10, 10, 0, "Normal", "Default", System::Black, System::Blue, "|+O+|");
	BaseObject* temp2 = new Enemy();
	players.push_back(temp2);
	players[0]->SetLife(true);
	players[1]->SetLife(true);
	players.push_back(new Missle());
	players[2]->SetLife(false);
	Player* player1 = dynamic_cast<Player*>(players[0]);
	Missle* m = dynamic_cast<Missle*>(players[2]);
	//players.push_back(m);
	
	player1->SetMissile(m);
#endif
#pragma endregion

#pragma region istream
#if 0
	players = new BaseObject*[3];
	BaseObject** temp;
	temp = new BaseObject*[3];
	int fg, bg;
	int size = 0;
	char buffer[32];
	fstream fin;
	fin.open("savefile.txt",ios_base::in);
	if (fin.is_open())
	{
		fin >> size;
		for (int i = 0; i < size; ++i)
		{

			fin.ignore(INT_MAX, '\n');
			fin.getline(buffer, INT_MAX, '\t');
			fin >> bg >> fg;

			temp[i] = new BaseObject(0, System::Console::CursorTop() + 2, (System::ConsoleColor)fg, (System::ConsoleColor)bg, buffer);



		}

		//Player(int _x, int _y, int _score, int _diff, const char* const _name, System::ConsoleColor _fg, System::ConsoleColor _bg, const char* const _image);
		char username[32];
		for (;;)
		{
			cout << "What is your name? " << endl;
			if (cin.get(username, 32))
			{
				cin.sync();
				break;

			}
			cin.clear();
			cin.ignore();
			system("cls");
		}
		players[0] = new Player(15, 15, 0, 1, username, temp[0]->GetFB(), temp[0]->GetBG(), temp[0]->GetImage());
		int enemychoice;
		for (;;)
		{
			cout << "What do you want as an enemy?\n";
			cout << "1) Card" << endl;
			cout << "2) Ship" << endl;
			if (cin >> enemychoice&&enemychoice>0 && enemychoice<3)
			{
				cin.sync();
				break;

			}
		}

		switch (enemychoice)
		{
		case 1:
		{
			players[1] = new Enemy(10, 5, temp[1]->GetFB(), temp[1]->GetBG(), temp[1]->GetImage());

			break;
		}
		case 2:
		{

			players[1] = new Enemy(10, 5, temp[2]->GetFB(), temp[2]->GetBG(), temp[2]->GetImage());
			break;
		}


		}

		players[2] = NULL;
		system("cls");
		for (int i = 0; i < 2; ++i)
		{
			players[i]->Render();

		}

	}

	fin.close();
	for (int i = 0; i < 3; ++i)
	{
		delete temp[i];
	}
	delete[]temp;

#endif
#pragma endregion
#pragma region Dead Code
#if 0
	BaseObject card(0, 2, (System::ConsoleColor)12, (System::ConsoleColor)15, "+---+\n|A  |\n| H |\n|  A|\n+---+"),
		dice(0, 8, (System::ConsoleColor)0, (System::ConsoleColor)15, "* *\n * \n* *");
	cout << "Before:\n";

	card.Render(); cout << '\n';

	dice.Render(); cout << '\n';
	BaseObject temp = card;
	card = dice;
	dice = temp;
	cout << '\n';
	cout << "After:\n";
	card.SetX(0);
	card.SetY(14);
	card.Render(); cout << '\n';
	dice.SetX(0);
	dice.SetY(18);
	dice.Render(); cout << '\n';
	system("pause");
	system("cls");

	BaseObject ship(0, 0, (System::ConsoleColor)8, (System::ConsoleColor)0, "|O|");

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

		shiptot[i].SetX(currx * 4);
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
	//delete[]shiptot;
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