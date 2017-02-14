// OBP_Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"Game.h"
#include"DList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);

	srand(unsigned int(time(0)));

	Game g;
	g.Play();
#pragma region DLIST
#if 0
	typedef DList<char> OurDList;
	OurDList testDList;
	testDList.push_front('#');
	testDList.push_back('@');
	testDList.Clear();
	testDList.push_back('i');
	testDList.push_front('r');
	testDList.push_front('h');
	testDList.push_back('s');
	testDList.push_front('t');
	testDList.erase(2);
	testDList.erase(0);
	testDList.erase(2);
	for (int i = 0; i < testDList.size(); i++)
		cout << testDList[i];
	testDList.erase(0);
	testDList.erase(0);
	testDList.push_front('!');
	testDList.push_back('\"');
	testDList.erase(1);
	for (int i = 0; i < testDList.size(); i++)
		cout << testDList[i];
	cout << flush << endl;
	system("pause");
#endif
#pragma endregion
	return 0;
}

