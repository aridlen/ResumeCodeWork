#pragma once

enum STATE_IDS{ MENU_STATE = 0,PLAY_STATE,HIGHSCORES_STATE,MAX_STATES };
class BaseObject;
class IBaseState;
#define ALIVE_FLAG 1<<0
#define GHOST_FLAG 1<<1
#define MOVE_FLAG 1<<2
#define SHOOT_FLAG 1<<3

class Game
{
private:

	static char cheats;
	static IBaseState**states;
	static IBaseState* currentstate;

	int frame=0;
	bool play=true;

	
public:
	Game();
	~Game();
	void Play();
	void Input();
	void Update(int _Frame);
	void Render() const;
	static void ChangeState(STATE_IDS _state);
	static char& GetCheats() { return cheats; }
	static void SetCheats(char _cheats){ cheats = _cheats; }
};

