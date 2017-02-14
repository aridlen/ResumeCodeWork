#include "stdafx.h"
#include "HighScores.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "Player.h"
bool NameSortAscending(PlayInfo& _a, PlayInfo& _b)
{
	if (_strcmpi(_a.name, _b.name) < 0)
		return true;
	else
		return false;
}
bool NameSortDescending(PlayInfo& _a, PlayInfo _b)
{
	if (_strcmpi(_a.name, _b.name) > 0)
		return true;
	else
		return false;
}

bool ScoreDescending(PlayInfo& _a, PlayInfo& _b)
{
	return _a.score > _b.score;
}
void DifficultyHardest()
{
	vector<PlayInfo>temphard;
	decltype(HighScores::GetHighScores().size())i = 0;
	for (; i < HighScores::GetHighScores().size(); ++i)
	{

		if (strcmp(HighScores::GetHighScores()[i].diff, "Hard")==0)
		{
			temphard.push_back(HighScores::GetHighScores()[i]);

		}

	}
	sort(temphard.begin(), temphard.end(), ScoreDescending);
	
	//for_each(temphard.begin(), temphard.end(), DisplayScore);
	
	for (i=0; i < temphard.size(); ++i)
	{
		cout << temphard[i].name << " scored " << temphard[i].score << " on " << temphard[i].diff << endl;
		
	}
	
	vector<PlayInfo>tempnormal;

	for (i = 0; i < HighScores::GetHighScores().size(); ++i)
	{

		if (strcmp(HighScores::GetHighScores()[i].diff, "Normal")==0)
		{
			tempnormal.push_back(HighScores::GetHighScores()[i]);

		}

	}
	sort(tempnormal.begin(), tempnormal.end(), ScoreDescending);
	//for_each(tempnormal.begin(), tempnormal.end(), DisplayScore);
	for (i=0; i < tempnormal.size(); ++i)
	{
		cout << tempnormal[i].name << " scored " << tempnormal[i].score << " on " << tempnormal[i].diff << endl;

	}
	vector<PlayInfo>tempeasy;

	for (i = 0; i < HighScores::GetHighScores().size(); ++i)
	{

		if (strcmp(HighScores::GetHighScores()[i].diff,"Easy")==0)
		{
			tempeasy.push_back(HighScores::GetHighScores()[i]);

		}

	}
	sort(tempeasy.begin(), tempeasy.end(), ScoreDescending);
	//for_each(tempeasy.begin(), tempeasy.end(), DisplayScore);
	for (i=0; i < tempeasy.size(); ++i)
	{
		cout << tempeasy[i].name << " scored " << tempeasy[i].score << " on " << tempeasy[i].diff << endl;

	}
}
void DisplayScore(PlayInfo& _info)
{
	cout << _info.name << " scored " << _info.score << " on " << _info.diff << endl;

}
HighScores::HighScores()
{
}


HighScores::~HighScores()
{
	
}

void HighScores::Input()
{
	if (GetAsyncKeyState('W') && !keyspressed)
	{
		--scorechoice;
		if (scorechoice < 0)
		{
			scorechoice = 4;
		}
		keyspressed = true;
	}
	if (GetAsyncKeyState('S') && !keyspressed)
	{
		++scorechoice;
		if (scorechoice > 4)
		{
			scorechoice = 0;
		}
		keyspressed = true;
	}
	if (GetAsyncKeyState(VK_RETURN) && !keyspressed)
	{
		keyspressed = true;
		switch (scorechoice)
		{
		case 0:
		{
			
			System::Console::FlushKeys();
			system("cls");
			sort(final_scores.begin(), final_scores.end(), NameSortAscending);
			for_each(final_scores.begin(), final_scores.end(), DisplayScore);
			cout << '\n';
			SaveText();
			system("pause");
			System::Console::FlushKeys();
			break;
		
		}
		case 1:
		{
			System::Console::FlushKeys();
			system("cls");
			sort(final_scores.begin(), final_scores.end(), NameSortDescending);
			for_each(final_scores.begin(), final_scores.end(), DisplayScore);
			cout << '\n';
			SaveText();
			system("pause");
			System::Console::FlushKeys();
			break;
		}
		case 2:
		{
			System::Console::FlushKeys();
			system("cls");
			sort(final_scores.begin(), final_scores.end(), ScoreDescending);
			for_each(final_scores.begin(), final_scores.end(), DisplayScore);
			cout << '\n';
			SaveText();
			system("pause");
			System::Console::FlushKeys();
			break;
		}
		case 3:
		{
			System::Console::FlushKeys();
			Sleep(200);
			cin.sync();
			system("cls");
			DifficultyHardest();
			SaveText();
			system("pause");
			System::Console::FlushKeys();
			break;
		}
		case 4:
		{
			Game::ChangeState(MENU_STATE);
		}
		}
	}
}
void HighScores::Update(int _frame)
{
	if (!GetAsyncKeyState('W') && !GetAsyncKeyState('S') && !GetAsyncKeyState(VK_RETURN))
	{
		keyspressed = false;
	}
}
void HighScores::Render() const
{
	for (int i = 0; i < 5; ++i)
	{

		if (i == scorechoice)
		{
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 13, 10 + i);
			cout << "-->";
		}
		else
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 10, 10 + i);

		cout << highscoremenu[i] << '\n';
	}
}
void HighScores::Enter()
{
	cin.sync();
	Sleep(200);
	final_scores.clear();
	scorechoice = 0;
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
	/*fstream bout;
	bout.open("scores.bin", ios_base::binary | ios_base::out | ios_base::trunc);
	if (bout.is_open())
	{
		for (int i = 0; i < (int)final_scores.size(); ++i)
		{
			bout.write((char*)&final_scores[i], sizeof(PlayInfo));

		}
		bout.close();
	}*/



	keyspressed = true;

}
void HighScores::Exit()
{
	
}
void HighScores::Init()
{
	scorechoice = 0;
	strcpy_s(highscoremenu[0], 128, "Name (A-Z)");
	strcpy_s(highscoremenu[1], 128, "Name (Z-A)");
	strcpy_s(highscoremenu[2], 128, "Best Scores");
	strcpy_s(highscoremenu[3], 128, "Champions");
	strcpy_s(highscoremenu[4] ,128, "Exit");
}
void HighScores::SaveText()
{
	
	keyspressed = true;
	char yesno;
	for (;;)
	{
		cout << "Do wish to save these scores in a textfile?(y/n)" << endl;
		if (cin >> yesno && ((yesno == 'y' || yesno == 'Y') || (yesno == 'n' || yesno == 'N')) && cin.good())
		{ 
			cin.sync();
			break;
		}
		cin.clear();
		cin.ignore();
	}
	
	char filename[32];
	if (yesno == 'y' || yesno == 'Y')
	{
		int amount;
		for (;;)
		{
			cout << "How many from the top down do you wish to save(PRESS 0 FOR ALL): ";
			if (cin.good() && cin >> amount&&amount >= 0 && amount <= (int)final_scores.size())
			{
				cin.sync();
				break;
			}
			cin.clear();
			cin.ignore();
			system("cls");
		}
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

			decltype(final_scores.size())i = 0;
			if (amount == 0)
			{
				for (; i < final_scores.size(); ++i)
				{
					fout << final_scores[i].name << '\t' << final_scores[i].score << '\t' << final_scores[i].diff << '\n';
				}
			}
			else
			{
				for (; (int)i < amount; ++i)
				{
					fout << final_scores[i].name << '\t' << final_scores[i].score << '\t' << final_scores[i].diff << '\n';
				}
			}
			fout.close();
		}
	}
	else
		return;
	keyspressed = false;
}