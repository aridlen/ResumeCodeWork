#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: TJ Davis              //
//      Date:  AUGUST 2015               //
//                                       //
///////////////////////////////////////////
#include "IBaseState.h"
#include "Cell.h"
#include"DList.h"
struct PlayInfo;
class BaseObject;

class PlayState :
	public IBaseState
{
private:
	
	static DList<BaseObject*> players;
	Cell<int, char>*cellimage;
	int cellsize;
	bool readin = false;
	 //int checknum = 0;
public:
	PlayState();
	~PlayState();

	void Input();
	void Update(int _frame);
	void Render()const;

	void Enter();
	void Exit();

	void Init();
	static DList<BaseObject*>& GetPlayers(){ return players; }
	
};

