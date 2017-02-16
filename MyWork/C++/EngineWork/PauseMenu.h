#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//      Date:  01/02/2017                //
//                                       //
///////////////////////////////////////////
#include "UIPrinter.h"
#include "GamePad.h"
#include"OptionsScreen.h"
class PauseMenu
{
	UIPrinter m_Ui;
	UIimage m_background;
	Button m_Continue;
	Button m_Retry;
	Button m_Options;
	Button m_Exit;
	bool active;
	bool ResetLevel;
	bool ExittoMain;
	float m_currentTime;
	int m_selected;
	GamePad::ButtonStateTracker gbt;
	OptionsScreen* m_inGameoptions;
	bool inOptions;
public:
	PauseMenu();
	PauseMenu(ResourceManager* res, OptionsScreen* options);
	void Run(ResourceManager* res, float dt,AudioManager* media);
	void Shutdown();
	bool GetActive() { return active; }
	void ToggleActive() { active = !active; }
	bool GetRetry() { return ResetLevel; }
	void ToggleRetry() { ResetLevel = !ResetLevel; }
	bool GetExit() { return ExittoMain; }
	void ToggleExit() { ExittoMain = !ExittoMain; }
	~PauseMenu();
};

