#include "Teapot.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include <glut.h>
#include <time.h>
#include <windows.h>


Teapot::Teapot() {
	// use random numbers to initialise the position, scale and velocity

	position.x = 10 * (float)rand() / (RAND_MAX) - 5;
	position.y = 10 * (float)rand() / (RAND_MAX) - 5;
	position.z = RandomFloatBetween(0.0f, 6.0f);

	scale = RandomFloatBetween(0.3f, 0.5f);


	velocity.x = 1000* (float)rand() / ((RAND_MAX)* 1000) - .001;
	velocity.y = 1000* (float)rand() / ((RAND_MAX)* 1000) - .001;
	velocity.z = 1000* (float)rand() / ((RAND_MAX)* 1000) - .001;

	mSoundBounce = new Sound();
	mSoundBounce->Load("Sounds/Bounce.wav");

	boundingSphere = new Sphere(position, scale*1.4);
	mAcceleration = Vector3D(1.0f, 1.0f, 1.0f);
	mInelastic = Vector3D(0.7f, 0.7f, 0.7f);
	mGravity = Vector3D(0.0f, 0.0f, -0.96f);
	mReversedDir = true;
}

float Teapot::RandomFloatBetween(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void Teapot::Render() { 
	if (boundingSphere->GetCollided())
	{
		glColor3f(1.0, 0.0, 0.0);
		if (mReversedDir == true)
		{
			velocity.x *= -mInelastic.x;
			velocity.y *= -mInelastic.y;
			velocity.z *= -mInelastic.z;
			mReversedDir = false;
			mCollisionCount++;
		}

	}
	else 
	{
		glColor3f(0.0, 1.0, 0.0);
		mReversedDir = true;
	}

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		//glutWireTeapot(scale);
		glPolygonMode(GL_FRONT, GL_FILL);
		glutSolidSphere(boundingSphere->GetBoundingRadius(), 10, 10);
		//glColor3f(0.0, 0.0, 0.0);
		//glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

}

void Teapot::Update(float deltaTime) {
	boundingSphere->SetCollided(false);
	position.x += velocity.x * deltaTime + mAcceleration.x * (0.5 * deltaTime * deltaTime);
	position.y += velocity.y * deltaTime + mAcceleration.y * (0.5 * deltaTime * deltaTime);
	position.z += velocity.z * deltaTime + mAcceleration.z * (0.5 * deltaTime * deltaTime);

	velocity.z += mGravity.z * deltaTime;

	//velocity.x += mAcceleration.x * deltaTime;
	//velocity.y += mAcceleration.y * deltaTime;
	//velocity.z += mAcceleration.z * deltaTime;

	//velocity = velocity * 0.98f;

	if (position.x > 5 || position.x < -5)
		velocity.x *= -1;

	if (position.y > 5 || position.y < -5)
		velocity.y *= -1;

	if (position.z > 6)
		velocity.z *= -1;

	if (position.z < 1)
	{

		velocity.z *= -1;
		velocity.z *= mInelastic.z;	

		if (mIsSoundPlayed == false)
		{		
			mSoundBounce->Play(0);
			mIsSoundPlayed = true;
		}
	}

	if (mCollidedWithPlayer == true)
	{
		position.x = mCollidedPos.x + mPlayerColPos->x;
		position.y = mCollidedPos.y + mPlayerColPos->y;
		position.z = 1.0f;

	}



	boundingSphere->Update(position);
}

Sphere * Teapot::GetBoundingSphere() {
	return boundingSphere;
}

