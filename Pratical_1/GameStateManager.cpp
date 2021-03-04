#include "GameStateManager.h"
#include "Practical_2.h"
#include "Practical_3.h"
#include "Practical_4.h"
#include "Practical_5.h"
#include "Practical_6.h"
#include "Practical_7.h"

//singleton
GameStateManager* GameStateManager::sInstance = NULL;

GameStateManager* GameStateManager::getInstance()
{
	if (GameStateManager::sInstance == NULL)
	{
		sInstance = new GameStateManager;
	}

	return sInstance;
}

void GameStateManager::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

GameStateManager::GameStateManager()
{
	currentState = 0;
	framesToUpdate = 0;
	preState = 0;

	Practical_2* practical_2 = new Practical_2();
	practical_2->init();
	stateList.push_back(practical_2);

	Practical_3* practical_3 = new Practical_3();
	practical_3->init();
	stateList.push_back(practical_3);

	Practical_4* practical_4 = new Practical_4();
	practical_4->init();
	stateList.push_back(practical_4);

	Practical_5* practical_5 = new Practical_5();
	practical_5->init();
	stateList.push_back(practical_5);

	Practical_6* practical_6 = new Practical_6();
	practical_6->init();
	stateList.push_back(practical_6);

	Practical_7* practical_7 = new Practical_7();
	practical_7->init();
	stateList.push_back(practical_7);

	gTime = new GTime();
	gTime->init(60);
}

GameStateManager::~GameStateManager()
{
	for (int i = 0; i < stateList.size(); i++)
	{
		stateList[i]->release();
		delete stateList[i];
		stateList[i] = NULL;
	}

	delete gTime;
}

void GameStateManager::update()
{
	stateList[currentState]->update();

	framesToUpdate = gTime->framesToUpdate();

	for (int i = 0; i < framesToUpdate; i++)
	{
		stateList[currentState]->fixedUpdate();
	}

}

void GameStateManager::draw()
{
	stateList[currentState]->draw();
}