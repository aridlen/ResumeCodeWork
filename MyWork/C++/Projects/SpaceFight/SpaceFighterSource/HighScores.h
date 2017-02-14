#pragma once
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
	/*bool NameSortAscending(PlayInfo& _a, PlayInfo& _b);
	bool NameSortDescending(PlayInfo& _a, PlayInfo _b);
	
	bool ScoreDescending(PlayInfo& _a, PlayInfo& _b);
	bool DifficultyHardest(PlayInfo& _a, PlayInfo& _b);
	void DisplayScore(PlayInfo& _info);*/
	void SaveText();
    static vector<PlayInfo>& GetHighScores(){ return final_scores; }
};

