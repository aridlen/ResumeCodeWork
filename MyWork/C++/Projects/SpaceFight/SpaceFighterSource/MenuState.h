#pragma once
#include "IBaseState.h"
class MenuState :
	public IBaseState
{
private:
	int menunum = 0;
	char menuText[4][128];
	bool keypress = false;
public:
	MenuState();
	~MenuState();

 void Input();
 void Update(int _frame);
 void Render()const;

 void Enter();
 void Exit();

 void Init();

 

};

