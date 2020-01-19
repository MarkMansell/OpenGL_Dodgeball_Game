#pragma once
#include "Commons.h"
#include "Sound.h"


class Sphere;
class Teapot {
public:
	Teapot();
	~Teapot() { }
	void Update(float deltaTime);
	void Render();
	Sphere * GetBoundingSphere();
	void SetCollided(bool collided){ mCollided = collided; }
	bool GetCollided(){ return mCollided; }
	int GetCollisionCount() { return mCollisionCount; }
	bool GetCollidedWithPlayer() { return mCollidedWithPlayer; }
	void SetCollidedWithPlayer(bool collided, Vector3D* playerpos){ mCollidedWithPlayer = collided; mPlayerColPos = playerpos; mCollidedPos = position; }
	float RandomFloatBetween(float a, float b);

private:
	Sound* mSoundBounce;
	Vector3D* mPlayerColPos;
	Vector3D mCollidedPos;
	Vector3D position;
	float scale;
	Vector3D velocity;
	Sphere * boundingSphere;
	bool mCollided;
	Vector3D mAcceleration;
	Vector3D mInelastic;
	Vector3D mGravity;
	bool mReversedDir; 
	bool mCollidedWithPlayer;
	bool mIsSoundPlayed;
	int mCollisionCount;

};