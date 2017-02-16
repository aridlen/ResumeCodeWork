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

#include "Player.h"
#include "Game.h"
class HighScores :
	public IBaseState
{
private:
	static vector<PlayInfo> final_scores;
	char highscoremenu[5][128];
	int scorechoice;
	bool keyspressed = false;
public:
	HighScores();
	~HighScores();
	void Input();
	void Update(int _frame);
	void Render() const;
	void Enter();
	void Exit();
	void Init();
	void SaveText();
	//ACCESSORS
    static vector<PlayInfo>& GetHighScores(){ return final_scores; }
	//MUTATORS


};

