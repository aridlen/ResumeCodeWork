#pragma once
#include"UIPrinter.h"
class Win_Lose
{
	bool m_win;
	bool m_lose;
	UIPrinter m_UI;
	UIimage m_winUI;
	UIimage m_loseUI;
	float dt;
public:
	Win_Lose();
	Win_Lose(ResourceManager* res);
	~Win_Lose();
	void Update(ResourceManager* res, Player* player, LevelManager* lvl,float time, AudioManager* media);
	void ResetConditions();
	void Shutdown();
};

