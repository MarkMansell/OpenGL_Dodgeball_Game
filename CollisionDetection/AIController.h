#pragma once
#include "object3DS.h"
#include "Commons.h"
#include "Sound.h"

enum AIState{
	ATTACKING,
	COLLECTING,
	IDLE
};

class AIController
{
public:
	AIController(object3DS* aiplayer, Vector3D* playerpos, Vector3D* collectable);
	~AIController();

	void Update(float delta);

	void SetWaypoint(Vector3D* pos);
	void ObjectCollected();
	void PlayerCollected();
	void SetState(AIState state){ mCurrentState = state; }
	AIState GetState() { return mCurrentState; }
	void MoveTowards(Vector3D* pos);
	void DelayForTime(float delta);
	void GenerateState();
	void SetScorePointers(int* aiscore, int* playerscore){ mPoints = aiscore; mPlayerPoints = playerscore; }
private:
	AIState mCurrentState;
	object3DS* mAIPlayer;
	Vector3D* mPlayer1Pos;
	Vector3D* mCurrentWaypoint;
	bool mIsAttacking;
	int* mPoints;
	int* mPlayerPoints;
	float mSpeed;
	float mDelayTime;
	float mTotalTime;
};

