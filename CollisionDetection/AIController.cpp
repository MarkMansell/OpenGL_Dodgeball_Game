#include "AIController.h"


AIController::AIController(object3DS* aiplayer, Vector3D* playerpos, Vector3D* collectable) : mAIPlayer(aiplayer)
{
	mAIPlayer = aiplayer;
	mPlayer1Pos = playerpos;
	mCurrentState = IDLE;
	mCurrentWaypoint = collectable;
	mSpeed = 0.03f;
	mDelayTime = 4.0f;
	mTotalTime = 0.0f;
	mIsAttacking = true;
}


AIController::~AIController()
{
}

void AIController::Update(float delta)
{
	switch (mCurrentState)
	{
	case ATTACKING:
		MoveTowards(mPlayer1Pos);		
		break;
	case COLLECTING:
		MoveTowards(mCurrentWaypoint);		
		break;
	case IDLE:
		DelayForTime(delta);
		break;
	default:
		break;
	}
}

void AIController::SetWaypoint(Vector3D* pos)
{
	mCurrentWaypoint = pos;
}

void AIController::ObjectCollected()
{
	SetState(IDLE);
}

void AIController::PlayerCollected()
{
	if (mDelayTime > 2.0f)
	{
		mDelayTime -= 0.2f;
	}
	if (mSpeed < 10.0f)
	{
		mSpeed += 0.005f;
	}
	GenerateState();
}

void AIController::MoveTowards(Vector3D* pos)
{
	float epsilon = 0.5f;
	Vector3D dir = *pos - mAIPlayer->mgPosition;
	dir.normalise();
	mAIPlayer->mgPosition.x += dir.x * mSpeed;
	mAIPlayer->mgPosition.y += dir.y * mSpeed;

	if (abs(pos->x - mAIPlayer->mgPosition.x) <= epsilon && abs(pos->y - mAIPlayer->mgPosition.y) <= epsilon)
	{
		if (mCurrentState == ATTACKING && mIsAttacking == true)
		{
			*mPlayerPoints = *mPlayerPoints - 1;
			mIsAttacking = false;
			SetState(IDLE);
		}
		SetState(IDLE);
		mIsAttacking = true; 
	}
}

void AIController::DelayForTime(float delta)
{
	mTotalTime += delta;
	if (mTotalTime > mDelayTime)
	{
		mTotalTime = 0.0f;
		GenerateState();
	}
}

void AIController::GenerateState()
{
	if (*mPoints < *mPlayerPoints - 1)
	{
		SetState(ATTACKING);
	}
	else
	{
		SetState(COLLECTING);
	}
}