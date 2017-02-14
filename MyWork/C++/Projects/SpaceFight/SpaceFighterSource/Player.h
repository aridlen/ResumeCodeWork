#pragma once
#include "BaseObject.h"
#include"DList.h"
class Missle;
struct PlayInfo
{
	char name[16];
	int score;
	char diff[8];
	
	/*bool operator<(PlayInfo& _x)
	{

	}*/
};
class Player :
	public BaseObject
{
private:
	string name;
	int score;
	int lifepoints;
	string difficulty;
	Missle* m;
	string lifed="          ";
public:
	Player();
	Player(int _x, int _y, int _score, string _diff, const char* const _name, System::ConsoleColor _fg, System::ConsoleColor _bg, const char* const _image);
	~Player();


	Player(Player const& _cpy);
	Player& operator=(Player const& _assign);
	const char* const GetName(){ return name.c_str(); }
	int GetScore()const { return score; }
	const char* const GetDiff(){ return difficulty.c_str(); }
	Missle* GetMissile() const { return m; }
	int GetLP()const{ return lifepoints; }
	string GetLD()const{ return lifed.c_str(); }

	void SetLD(const char* const _display){ lifed=_display; }
	void SetLP(int _lp){ lifepoints = _lp; }
	void SetName(const char* const _name){ name = _name; }
	void SetScore(int _score){ score = _score; }
	void SetDiff(string _diff){ difficulty = _diff; }
	void SetMissile(Missle* _m){ m = _m; }
	
	void Input(DList<BaseObject*>& _p);
	void Update(int _frame);
	void Render()const;
};

