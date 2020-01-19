#include "Collectable.h"
#include <windows.h>
#include "Collision.h"
#include <glut.h>

Collectable::Collectable(GLuint textureid)
{	
	mBoundingSphere = new Sphere(Vector3D(0.0f, 0.0f, 0.0f), 0.5f);

	mObject = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/Collectable.3ds");
	mObject->SetTexture(textureid);
	mCollectedSound = new Sound();
	mCollectedSound->Load("Sounds/Collectable.wav");
	mRotSpeed = 40.0f;	
	GenerateNewPosition();
}


Collectable::~Collectable()
{
}


void Collectable::Update(float deltaTime)
{
	mAngle += mRotSpeed * deltaTime;
}

void Collectable::Render()
{
	glPushMatrix();
		glTranslatef(mPosition.x, mPosition.y, mPosition.z);
		glRotatef(mAngle, 0.0f, 0.0f, 1.0f);
		glPolygonMode(GL_FRONT, GL_FILL);	
		mObject->render();
	glPopMatrix();
}

void Collectable::GenerateNewPosition()
{
	mPosition.x = 14 * (float)rand() / (RAND_MAX)-7;
	mPosition.y = 14 * (float)rand() / (RAND_MAX)-7;
	mPosition.z = 1.0f;
	mCollectedSound->Play(0);
	mBoundingSphere->Update(mPosition);
}
