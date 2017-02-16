#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: TJ Davis              //
//      Date:  AUGUST 2015               //
//                                       //
///////////////////////////////////////////
#include "BaseObject.h"
#include"DList.h"
#define velX velVec[0]
#define VelY velVec[1]
class Missle :
	public BaseObject
{
private:
	vector<int> velVec;

public:
	Missle();
	~Missle();
	//ACCESSORS
	int GetXvel()const { return velX; }
	int GetYvel() const { return VelY; }
	
	//MUTATORS
	void SetVelocity(int _x, int _y){ velX = _x; VelY = _y; }

//////////////////////////////////////////////////
	void RenderingLife();
	void Input(DList<BaseObject*>&_p);
	void Update(int _frame);
	void Render() const;
};

