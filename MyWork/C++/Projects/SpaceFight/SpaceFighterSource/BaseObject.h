#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: TJ Davis              //
//      Date:  AUGUST 2015               //
//                                       //
///////////////////////////////////////////
#include"DList.h"
#include "Cell.h"
class BaseObject
{
private:

	 int width, height;
	int x, y;
	System::ConsoleColor fg,bg;
	string image;
	vector<Cell<int, char>*> imageobj;
	bool alive=false;

public:

	BaseObject();
	BaseObject(int _x, int _y, System::ConsoleColor _fg, System::ConsoleColor _bg,const char* const _image);
	BaseObject(BaseObject const& _obj);
	BaseObject& operator=(BaseObject const& _cpy);
	virtual ~BaseObject();
	virtual void Render() const;
	//ACCESSORS
	int GetX(){ return x; }
	int GetY(){ return y; }
	System::ConsoleColor GetFB()const { return fg; }
	System::ConsoleColor GetBG()const { return bg; }
	const char* const GetImage()const { return image.c_str(); }
	 int GetWidth(){ return width; }
	 int GetHeight(){ return height; }
	 bool GetLife()const { return alive; }
	 int CellSize()const{ return imageobj.size(); }

	 //MUTATORS
	void SetX(int _x) { x = _x; }
	void SetY(int _y){ y = _y; }
	void SetLife(bool _live){ alive = _live; }
	void SetFG(System::ConsoleColor _fg){ fg = _fg; }
	void SetBG(System::ConsoleColor _bg){ bg = _bg; }
	void SetImage(const char* const _image);
	void SetW(unsigned int _w){ width = _w; }
	void SetH(unsigned int _h){ height = _h; }
	//////////////////////////////////////////////////
	bool NewCollision(BaseObject* _p, int _x, int _y);
	
	
	virtual void Input( DList<BaseObject*>& _p);
	virtual void Update(int _frame);

};

