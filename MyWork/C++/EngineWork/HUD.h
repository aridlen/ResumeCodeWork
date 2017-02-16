#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//      Date:  01/02/2017                //
//                                       //
///////////////////////////////////////////
#include "UIPrinter.h"
class HUD
{
	UIPrinter m_UI;
	UIimage m_score;
	UITEXT m_scoreNum;
	UIimage m_comboBack;
	UITEXT m_comboCount;
	int combo;
	int m_playerScore;
	int setCheck;
	int prevScore;
	unsigned multiplier;
	int adder;
public:
	HUD();
	HUD(ResourceManager* res);
	void Run(ResourceManager* res);
	void Shutdown();
	~HUD();
	void SetScoreString(int combo);
	void SetComboString(int currentCombo) { combo = currentCombo; }
};

