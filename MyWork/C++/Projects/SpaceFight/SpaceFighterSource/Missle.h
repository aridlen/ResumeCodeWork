#pragma once
#include "BaseObject.h"
#include"DList.h"
#define velX velVec[0]
#define VelY velVec[1]
class Missle :
	public BaseObject
{
private:
	vector<int> velVec;
	//bool MissAlive = false;

public:
	Missle();
	~Missle();
	int GetXvel()const { return velX; }
	int GetYvel() const { return VelY; }
	//bool GetLife() const { return MissAlive; }
	
	void SetVelocity(int _x, int _y){ velX = _x; VelY = _y; }
	//void SetLife(bool _life){ MissAlive = _life; }

	void RenderingLife();
	void Input(DList<BaseObject*>&_p);
	void Update(int _frame);
	void Render() const;
};

