#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: TJ Davis              //
//      Date:  AUGUST 2015               //
//                                       //
///////////////////////////////////////////
template<typename offset, typename symbol>
struct Cell
{
	offset oX, oY;
	System::ConsoleColor fg, bg;
	symbol sym;

	Cell() { }
	Cell(offset _x, offset _y, System::ConsoleColor _fg, System::ConsoleColor _bg, symbol _sym);

	bool Show(int _left, int _top) const;
	///ACCESSORS
	offset GetX()const{ return oX; }
	offset GetY()const { return oY; }
	System::ConsoleColor GetFG()const{ return fg; }
	System::ConsoleColor GetBG()const { return bg; }
	symbol GetSYM()const { return sym; }
	//MUTATORS
	void SetOX(offset _ox){ oX = _ox; }
	void SetOY(offset _oy){ oY = _oy; }
	void SetFG(System::ConsoleColor _fg){ fg = _fg; }
	void SetBG(System::ConsoleColor _bg){ bg = _bg; }
	void SetSYM(symbol _sym){ sym = _sym; }
	///////////////////////////
	int operator[](int _indexX);
	const int operator[](int _indexY)const;

};

template<typename offset, typename symbol>
Cell<offset, symbol>::Cell(offset _x, offset _y, System::ConsoleColor _fg, System::ConsoleColor _bg, symbol _sym)
{
	SetOX(_x);
	SetOY(_y);
	SetFG(_fg);
	SetBG(_bg);
	SetSYM(_sym);

}
template<typename offset, typename symbol>
bool Cell<offset,symbol>::Show(int _left, int _top) const
{
	offset tempx = _left + oX;
	offset tempy = _top + oY;
	if (tempx > System::Console::WindowWidth() || tempx<1 || tempy > System::Console::WindowHeight() - 3 || tempy < 2)
	{
		return false;
	}
	System::Console::ForegroundColor(fg);
	System::Console::BackgroundColor(bg);
	System::Console::SetCursorPosition(tempx, tempy);
	cout << sym;
	System::Console::ResetColor();
	return true;
}
template<typename offset, typename symbol>
int Cell<offset,symbol>::operator[](int _indexX)
{
	if (_indexX == 0)
	{
		return oX;
	}
	if (_indexX == 1)
	{
		return oY;
	}
	return 0;
}
template<typename offset, typename symbol>
const int Cell<offset,symbol>::operator[](int _indexY)const
{
	if (_indexY == 0)
	{
		return oX;
	}
	if (_indexY == 1)
	{
		return oY;
	}
	return 0;

}
