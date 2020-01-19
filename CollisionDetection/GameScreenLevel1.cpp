#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include <vector>
#include "GameScreenManager.h"


#include <iostream>

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1(GameScreenManager* gsm) : GameScreen(gsm)
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	srand(time(NULL));
	for (int i = 0; i < 15; i++) {
		theTeapots.push_back(new Teapot());
	}


	mCharacter = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/Denzil.3ds");

	mTexCharacter = new Texture2D();
	mTexCharacter->Load("Textures/CharacterUV.raw", 64, 32);
	mCharacter->SetTexture(mTexCharacter->GetID());

	mCourt = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/Court.3ds");
	mTexCourt = new Texture2D();
	mTexCourt->Load("Textures/Court.raw", 512, 512);

	mCourt->SetTexture(mTexCourt->GetID());

	mCourtWalls = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/CourtWalls.3ds");

	//mTexCourtWalls = new Texture2D();
	//mTexCourtWalls->Load("Textures/WoodTexture.raw", 173, 173);
	//mCourtWalls->SetTexture(mTexCourtWalls->GetID());

	//mObj_Octopus->SetTexture(mTexCourt->GetID());
	mSoundDeath = new Sound();
	mSoundLevelComplete = new Sound();

	mSoundDeath->Load("Sounds/Scream.wav");
	mSoundLevelComplete->Load("Sounds/Level1Won.wav");
	
	mInput = new InputManager();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	mCollisionCount = 0;
	mCollisionNum = 0;
	mcollided = false;

	mCharacterSphere = new Sphere(mCharacter->mgPosition, 0.5f);
	mLevelEndPoint = new Sphere(Vector3D(0.0f, 5.0f, 0.0f), 0.9f);

	mCharacter->mgPosition.y = -5.0f;

	mHasLevelEnded = false;

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mInput->Update();
	mCharacterSphere->SetCollided(false);

	mCurrentTime += deltaTime; //Total time since level started

	for (int i = 0; i < theTeapots.size(); i++)
	{
		theTeapots[i]->Update(deltaTime);

		Collision::SphereSphereCollision(mCharacterSphere, theTeapots[i]->GetBoundingSphere());

		if (mCharacterSphere->GetCollided() == true)
		{
			if (theTeapots[i]->GetCollidedWithPlayer() == false)
			{
				theTeapots[i]->SetCollidedWithPlayer(true, &mCharacter->mgPosition);
				mCollisionNum++;
			}
			mCharacterSphere->SetCollided(false);
		}
	}

	for (int i = 0; i < theTeapots.size() - 1; i++)
	{
		for (int j = i + 1; j < theTeapots.size(); j++)
		{
			Collision::SphereSphereCollision(theTeapots[i]->GetBoundingSphere(), theTeapots[j]->GetBoundingSphere());
		}
	}

	CharacterController(mCharacter, deltaTime);
	mCharacterSphere->Update(Vector3D(mCharacter->mgPosition.x, mCharacter->mgPosition.y, mCharacter->mgPosition.z + 1.0f));


	Collision::SphereSphereCollision(mLevelEndPoint, mCharacterSphere);
	if (mLevelEndPoint->GetCollided() == true)
	{
		if (mHasLevelEnded == false)
		{
			mHasLevelEnded = true;
			mSoundLevelComplete->Play(0);
			EndOfLevel(false, mCurrentTime, mCollisionNum);
		}
	}

	if (mCollisionNum >= 4)
	{
		mSoundDeath->Play(0);
		EndOfLevel(true, mCurrentTime, 4);
	}
}

void GameScreenLevel1::EndOfLevel(bool failed, float time, int hitcount)
{
	if (failed == true)
	{
		mManager->SetLevelInfo(time, hitcount);
		mManager->ChangeScreen(SCREEN_GAMEOVER);
	}
	else
	{
		mManager->SetLevelInfo(time, hitcount);
		mManager->ChangeScreen(SCREEN_L1_Complete);
	}

}

void GameScreenLevel1::CharacterController(object3DS* character, float deltaTime)
{

	float characterspeed = 4.0f;
	if (mInput->IsKeyDown('W'))
	{
		character->mgPosition.y += characterspeed * deltaTime;
		//character->MoveFowards(characterspeed * deltaTime);
	}
	if (mInput->IsKeyDown('S'))
	{
		character->mgPosition.y -= characterspeed * deltaTime;
		//character->MoveFowards(-characterspeed * deltaTime);
	}

	if (mInput->IsKeyDown('A'))
	{
		character->mgPosition.x -= characterspeed * deltaTime;
	}
	if (mInput->IsKeyDown('D'))
	{
		character->mgPosition.x += characterspeed * deltaTime;
	}
	if (mInput->IsKeyDown('Q'))
	{
		character->mgRotation.z += characterspeed * deltaTime;
	}
	if (mInput->IsKeyDown('E'))
	{
		character->mgRotation.z -= characterspeed * deltaTime;
	}

}

void DrawPlane()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glEnd();
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	SetLight();
	SetMaterial();

	gluLookAt(0.0f, -10.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);


	for (int i = 0; i < theTeapots.size(); i++)
	{
		theTeapots[i]->Render();
	}

	glPushMatrix();
	mCharacter->render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(mCharacter->mgPosition.x, mCharacter->mgPosition.y, mCharacter->mgPosition.z + 1.0f);
	glutWireSphere(mCharacterSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

	//----------------------------------------------------------------------------------------------------Render Court----------------------------------------------------------------------
	glPushMatrix();
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	mCourt->render();
	//glScalef(3.0f, 3.0f, 3.0f);	
	//glDisable(GL_CULL_FACE);
	//mCourtWalls->render(); // Skybox
	//glEnable(GL_CULL_FACE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(mLevelEndPoint->GetCentre().x, mLevelEndPoint->GetCentre().y, mLevelEndPoint->GetCentre().z);
	glutWireSphere(mLevelEndPoint->GetBoundingRadius(), 10, 10);
	glPopMatrix();

	//---------------------------------------------------------------------------------------------------HUD-----------------------------------------------------------------------	
	DisplayHUD("Time: " + to_string(mCurrentTime), SCREEN_WIDTH / 2 - 50, 550);
	DisplayHUD("Balls Hit: " + to_string(mCollisionNum), SCREEN_WIDTH / 2 - 50, 525);
}

void GameScreenLevel1::SetLight() {
	lighting light = {
			{ 0.5f, 0.5f, 0.5f, 1.0f },
			{ 0.5f, 0.5f, 0.5f, 1.0f },
			{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel1::SetMaterial() {
	material material = {
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 0.9f, 0.9f, 0.9f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}


void GameScreenLevel1::DisplayHUD(string text, float x, float y)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos2d(x, y); //Location of text on screen
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
	glPopAttrib();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::CountCollision(Teapot* collided)
{
	if (collided->GetBoundingSphere()->GetCollided() == true)
	{
		if (collided->GetCollided() == false)
		{
			//mCollisionNum++;
			collided->SetCollided(true);
		}
	}

	if (collided->GetBoundingSphere()->GetCollided() == false)
	{
		collided->SetCollided(false);
	}
}