#include "stdafx.h"
#include "BaseObject.h"
#include"DList.h"
#include "Cell.h"
BaseObject::BaseObject()
{
	//image = NULL;
}


BaseObject::~BaseObject()
{
	for (int i = 0; i < CellSize();++i)
	delete imageobj[i];
	
}
BaseObject::BaseObject(int _x, int _y, System::ConsoleColor _fg, System::ConsoleColor _bg,const char* const _image)
{
	//image = NULL;
	//delete[] image;
	SetX(_x);
	SetY(_y);
	SetFG(_fg);
	SetBG(_bg);
	SetImage(_image);
	

}
BaseObject::BaseObject(BaseObject const& _obj)
{
	//image = NULL;
	//delete[] image;
	SetX(_obj.x);
	SetY(_obj.y);
	SetFG(_obj.fg);
	SetBG(_obj.bg);
	//SetImage(_obj.image);
	
}
BaseObject& BaseObject::operator=(BaseObject const& _cpy)
{
	if (this != &_cpy)
	{
		SetX(_cpy.x);
		SetY(_cpy.y);
		SetFG(_cpy.fg);
		SetBG(_cpy.bg);
		//SetImage(_cpy.image);
		
	}
	return *this;
}
void BaseObject::SetImage(const char* const _image)
{
	//delete[] image;

	//image = _strdup(_image);
	//image = _image;

	image = _image;
	int tempheight = 0;
	bool check = false;
	int i, j;
	i = j = 0;
	for (i; image[i]; ++i)
	{
		if (image[i] == '\n' || image[i] == '\t')
		{
			if (!check)
			{
				check = true;
				width = i;
			}

			++j;
		}
		else
		{
			imageobj.push_back(new Cell<int, char>(j, tempheight, fg, bg, image[i]));
			++j;
		}
	}
	
	
	if (!check)
		width = i;
	height = j;
	




}
void BaseObject::Render() const
{
	decltype(imageobj.size())i = 0;
	for (; i < imageobj.size(); ++i)
	{
		imageobj[i]->Show(x, y);
	}
	System::Console::ResetColor();

}


void BaseObject::Input(DList<BaseObject*>& _p)
{



}
void BaseObject::Update(int _frame)
{


}
bool BaseObject::NewCollision(BaseObject* _p, int _x, int _y)
	{

	for (unsigned int i = 0; i < imageobj.size(); ++i)
	{

		for (int j = 0; j < _p->CellSize(); ++j)
		{
			if ((imageobj[i]->GetX() + _x) == (_p->imageobj[j]->GetX() + _p->GetX()) && (imageobj[i]->GetY() + _y) == (_p->imageobj[j]->GetY() + _p->GetY()))
				return false;

		}

	}
	return true;
	}