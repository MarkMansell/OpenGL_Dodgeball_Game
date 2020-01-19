#pragma once
#include "Commons.h"
#include "object3DS.h"
#include "Sound.h"


class Sphere;

class Collectable
{
public:
	Collectable(GLuint textureid);
	~Collectable();

	void Render();
	void Update(float deltaTime);

	Sphere * GetBoundingSphere() { return mBoundingSphere; }
	bool GetCollided(){ return mCollided; }
	void SetCollided(bool collided){ mCollided = collided; }

	void GenerateNewPosition();
	Vector3D GetPosition() { return mPosition; }

	// Public Variables
	Vector3D mPosition;

private:
	bool mCollided;
	float mAngle;
	float mRotSpeed;
	object3DS* mObject;
	GLuint TexureID;
	Sphere* mBoundingSphere;
	Sound* mCollectedSound;
};

