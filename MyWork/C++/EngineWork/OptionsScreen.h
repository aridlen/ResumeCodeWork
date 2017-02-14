#pragma once
#include"UIPrinter.h"
#include"XTime.h"
#define NUMUIELEMENTS 3
class OptionsScreen
{
	UIPrinter optionsPrinter;
	UIimage options;
//	Button m_apply;
	Button m_yes;
	Button m_no;
	
	UIimage sliderButtonSound;
	UIimage sliderButtonBright;
	XTime m_timer;
	float m_time;
	unsigned int scroll1;
	int m_currentSelection;
	GamePad::ButtonStateTracker bst;
	bool Yes_No;
public:
	OptionsScreen();
	OptionsScreen(ResourceManager* res);
	~OptionsScreen();
	void CreateOptions(ResourceManager* device);
	int Run(ResourceManager* res, AudioManager* music,int transition);
	void Shutdown();

};

