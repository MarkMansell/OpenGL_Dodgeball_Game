#include "GameScreenLevel2.h"
#include <time.h>
#include "Constants.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include <string>

GameScreenLevel2::GameScreenLevel2(GameScreenManager* gsm) : GameScreen(gsm)
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								
	glEnable(GL_DEPTH_TEST);							

	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	srand(time(NULL));
	mInput = new InputManager();

	mCameraPos = Vector3D(0.0f, -15.0f, 10.0f);
	mCameraLookAt = Vector3D(0.0f, 0.0f, 0.0f);

	//---------------------------------------------------------------------------------------------------Create Character-----------------------------------------------------------------------	
	mCharacter = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/MinecraftPlayer.3ds");
	mTexCharacter = new Texture2D();
	mTexCharacter->Load("Textures/CharacterUV.raw", 64, 32);
	mCharacter->SetTexture(mTexCharacter->GetID());

	mCharacterVelocity = { 0.0f, 0.0f, 0.0f };

	//---------------------------------------------------------------------------------------------------Create FLoor-------------------------------------------------------------------------
	mFloor = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/Level2Floor.3ds");
	mTexFloor = new Texture2D();
	mTexFloor->Load("Textures/Level2Floor.raw", 512, 512);
	mFloor->SetTexture(mTexFloor->GetID());

	//---------------------------------------------------------------------------------------------------Create AI Character-----------------------------------------------------------------------	
	mAICharacter = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/MinecraftPlayer.3ds"); 
	mAICharacter->mgPosition = Vector3D(2.0f, 3.0f, 0.0f);

	mTexAICharacter = new Texture2D();
	mTexAICharacter->Load("Textures/AICharUV.raw", 64, 32);
	mAICharacter->SetTexture(mTexAICharacter->GetID());
	
	mTexAIEvil = new Texture2D();
	mTexAIEvil->Load("Textures/AICharEvilUV.raw", 64, 32);

	//---------------------------------------------------------------------------------------------------Initialize Variables------------------------------------------------------
	m_iP1BallsCollected = 0;
	m_iAIBallsCollected = 0;

	//---------------------------------------------------------------------------------------------------Create Collectable------------------------------------------------------
	mTexCollectable = new Texture2D();
	mTexCollectable->Load("Textures/DoughnutTexture.raw", 512, 512);

	mCollectable = new Collectable(mTexCollectable->GetID());
	mAIPlayer = new AIController(mAICharacter, &mCharacter->mgPosition, &mCollectable->mPosition);
	mAIPlayer->SetScorePointers(&m_iAIBallsCollected, &m_iP1BallsCollected);

	//---------------------------------------------------------------------------------------------------Initialize Collision------------------------------------------------------

	mCharacterBounding = new Sphere(mCharacter->mgPosition, 0.5f);
	mAIBounding = new Sphere(mAICharacter->mgPosition, 0.5f);

	mMusic = new Sound();
	mMusic->Load("Sounds/Minecraft_Dubstep.wav");
	mMusic->Play(1);

	mSoundAttacking = new Sound();
	mSoundAttacking->Load("Sounds/AIAttacking.wav");
	mAIAttackingSound = false;


	//---------------------------------------------------------------------------------------------------Initialize Textures and Lighting------------------------------------------------------
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


GameScreenLevel2::~GameScreenLevel2()
{
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	SetLight(); // Lighting
	SetMaterial(); // Materials
	glColor3f(0.0, 1.0, 0.0);

	gluLookAt(mCameraPos.x, mCameraPos.y, mCameraPos.z,
		0.0f, mCharacter->mgPosition.y, 0.0f,
		0.0f, 1.0f, 0.0f);


	glPushMatrix();
		mCharacter->render();
	glPopMatrix();

	glPushMatrix();
		mAICharacter->render();
	glPopMatrix();

	mCollectable->Render();

	glPushMatrix();
		mFloor->render();
	glPopMatrix();

	switch (mAIPlayer->GetState())
	{
	case ATTACKING:
		DisplayHUD("AI State: ATTACKING", SCREEN_WIDTH / 2 - 50, 500);
		break;
	case COLLECTING:
		DisplayHUD("AI State: Collecting", SCREEN_WIDTH / 2 - 50, 500);
		break;
	case IDLE:
		DisplayHUD("AI State: IDLE", SCREEN_WIDTH / 2 - 50, 500);
		break;
	}
	

	DisplayHUD("Balls Collected: " + to_string(m_iP1BallsCollected), SCREEN_WIDTH / 2 - 50, 550);
	DisplayHUD("AI Score: " + to_string(m_iAIBallsCollected), SCREEN_WIDTH / 2 - 50, 525);

}
void GameScreenLevel2::DisplayHUD(string text, float x, float y)
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
	glColor3f(1.0f, 0.0f, 0.0f);
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

void GameScreenLevel2::SetLight() {
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

void GameScreenLevel2::SetMaterial() {
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

void GameScreenLevel2::Update(float delta, SDL_Event e)
{
	mInput->Update();
	mAIPlayer->Update(delta);
	mCollectable->Update(delta);

	if (mAIPlayer->GetState() == ATTACKING)
	{
		mAICharacter->SetTexture(mTexAIEvil->GetID());
	}
	else
	{
		mAICharacter->SetTexture(mTexAICharacter->GetID());
	}

	if (Collision::SphereSphereCollision(mAIBounding, mCollectable->GetBoundingSphere()))
	{
		mCollectable->GenerateNewPosition();
		mCollectable->SetCollided(false);
		mAIPlayer->SetState(IDLE);
		m_iAIBallsCollected++;
	}		
		
	if (Collision::SphereSphereCollision(mCharacterBounding, mCollectable->GetBoundingSphere()))
	{
		mCollectable->GenerateNewPosition();
		mCollectable->SetCollided(false);
		mAIPlayer->PlayerCollected();
		m_iP1BallsCollected++;	
	}


	if (m_iAIBallsCollected >= 10)
	{
		mManager->SetLevel2Winner(false);
		mManager->ChangeScreen(SCREEN_L2_Complete);
		return;
	}
	if (m_iP1BallsCollected >= 10)
	{
		mManager->SetLevel2Winner(true);
		mManager->ChangeScreen(SCREEN_L2_Complete);
		return;
	}

	if (mInput->IsKeyDown('T'))
	{
		mCameraPos.y += 0.5f * delta;
	}
	if (mInput->IsKeyDown('G'))
	{
		mCameraPos.y -= 0.5f * delta;
	}

	if (mAIPlayer->GetState() == ATTACKING)
	{
		if (mAIAttackingSound == false)
		{
			mSoundAttacking->Play(0);
			mAIAttackingSound = true;
		}
	}
	if (mAIPlayer->GetState() == IDLE)
	{
		if (mAIAttackingSound == true)
		{
			mSoundAttacking->Stop();
			mAIAttackingSound = false;
		}
	}

	CharacterController(mCharacter, delta);
	mCharacterBounding->Update(Vector3D(mCharacter->mgPosition.x, mCharacter->mgPosition.y, mCharacter->mgPosition.z + 1.0f));
	mAIBounding->Update(Vector3D(mAICharacter->mgPosition.x, mAICharacter->mgPosition.y, mAICharacter->mgPosition.z + 1.0f));
}

void GameScreenLevel2::CharacterController(object3DS* player, float deltatime)
{
	float characterspeed = 15.0f;
	if (mInput->IsKeyDown('W'))
	{
		mCharacterVelocity.y += characterspeed * deltatime;
		mMovementInput = true;
	}
	if (mInput->IsKeyDown('S'))
	{
		mCharacterVelocity.y -= characterspeed * deltatime;
		mMovementInput = true;
	}

	if (mInput->IsKeyDown('A'))
	{
		mCharacterVelocity.x -= characterspeed * deltatime;
		mMovementInput = true;
	}
	if (mInput->IsKeyDown('D'))
	{
		mCharacterVelocity.x += characterspeed * deltatime;
		mMovementInput = true;
	}

	if (mMovementInput == false)
	{
		mCharacterVelocity.x *= 0.8f ;
		mCharacterVelocity.y *= 0.8f ;
		mCharacterVelocity.z *= 0.8f ;
	}

	player->mgPosition += mCharacterVelocity * deltatime;

	if (player->mgPosition.x > 8)
	{
		player->mgPosition.x = 8;
		mCharacterVelocity.x = 0;
	}

	if (player->mgPosition.x < -8)
	{
		player->mgPosition.x = -8;
		mCharacterVelocity.x = 0;
	} 

	if (player->mgPosition.y > 8)
	{
		player->mgPosition.y = 8;
		mCharacterVelocity.y = 0;
	}
	if (player->mgPosition.y < -8)
	{
		player->mgPosition.y = -8;
		mCharacterVelocity.y = 0;
	}

	mMovementInput = false;
}
