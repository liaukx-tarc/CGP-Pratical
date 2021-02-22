#ifndef GAMESTATEMANAGER
#include <stdio.h>
#include <vector>

#include "GameState.h"

class GameStateManager
{
private:
	static GameStateManager* sInstance;
	GameStateManager();
	~GameStateManager();

public:
	static GameStateManager* getInstance();
	static void releaseInsrance();

	int currentState, preState;
	std::vector<GameState*> stateList;

	void update();
	void draw();

};

#endif // !GAMESTATEMANAGER



