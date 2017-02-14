#pragma once
class IBaseState
{
private:


public:
	IBaseState();
	virtual ~IBaseState()=0;
	virtual void Input()=0;
	virtual void Update(int _frame)=0;
	virtual void Render()const=0;

	virtual void Enter()=0;
	virtual void Exit()=0;

	virtual void Init()=0;
};

