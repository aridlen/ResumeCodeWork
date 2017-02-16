#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//      Date:  01/02/2017                //
//                                       //
///////////////////////////////////////////
#include "UIPrinter.h"
#include "SimpleMath.h"

#include"OptionsScreen.h"
#include"XTime.h"
#include "GamePad.h"

class MenuState
{
	UIPrinter m_menu;
	Button m_start,m_options,m_highscores,m_exit;
	int m_currentState;
	XTime m_time;
	float time;
	/////
	/*bool buffer;
	unsigned int timer;*/
	UIimage background;
	GamePad::ButtonStateTracker bst;
	//Sounds m_music;
	bool back;
	unsigned int m_currentSong;
	OptionsScreen m_optionsSplash;
	int m_currentSelection;
	bool slowEnter;
	

public:
	MenuState(ResourceManager* res);
	MenuState();
	~MenuState();
	void Start(ResourceManager* res);
	void Run(ResourceManager* res, HWND win,AudioManager* media);
	void Shutdown();
	void CreateButton(ResourceManager* device, XMFLOAT2 pos);
	void SetCurrentState(int data) { m_currentState = data; }
	int GetCurrentState() { return m_currentState; }
	void SetMusicBack() { back = true; }
	void ToggleEnter() { slowEnter = !slowEnter; }
};

