#pragma once
#include "BaseObject.h"
#include"DList.h"
#define enex enemymove[0]
#define eney enemymove[1]
class Missle;
class Enemy :
	public BaseObject
{
private:
	vector<int> enemymove;
	int speed=0;
	int moveDir = 1;
	bool moved = false;
	bool player = false;
	bool tracking = false;
	BaseObject* target;
	Missle* enemiss;

public:
	Enemy();
	Enemy(int _x, int _y, System::ConsoleColor _fg, System::ConsoleColor _bg, const char* const _image);
	~Enemy();

	int GetXVel() const { return enex; }
	int GetYVel() const { return eney; }
	BaseObject* GetTarget() const { return target; }
	bool GetTracking() const { return tracking; }
	//Missle* GetMissile() const { return enemiss; }
	Enemy(Enemy const& _cpy);
	Enemy& operator=(Enemy const& _assign);

	//void SetMissile(Missle* _m){ enemiss = _m; }
	void SetTarget(BaseObject* _t) { target = _t; }
	void SetTracking(bool _h) { tracking = _h; }
	void SetXVel(int _x) { enex = _x; }
	void SetYVel(int _y) { eney = _y; }

	void Input(DList<BaseObject*>& _p);
	void Update(int _frame);
	void Render() const;
};

