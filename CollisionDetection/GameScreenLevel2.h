#pragma once

#include "GameScreen.h"
#include "GameScreenManager.h"
#include <string>
#include "object3DS.h"
#include "InputManager.h"
#include "Collision.h"
#include "AIController.h"
#include "Collectable.h"

using namespace std;

class GameScreenLevel2 : public GameScreen
{
public:
	GameScreenLevel2(GameScreenManager* gsm);
	~GameScreenLevel2(); 
	void Render();
	void Update(float deltaTime, SDL_Event e);

	void SetMaterial();
	void SetLight();

	void CharacterController(object3DS* player, float deltatime);
	void DisplayHUD(string text, float x, float y);

private:
	InputManager* mInput;
	AIController* mAIPlayer;
	Collectable* mCollectable;

	Sound* mMusic;
	Sound* mSoundAttacking;

	Vector3D mCharacterVelocity;
	bool mMovementInput;
	bool mAIAttackingSound;

	object3DS* mCharacter;
	object3DS* mAICharacter;
	object3DS* mFloor;

	Texture2D* mTexCharacter;
	Texture2D* mTexAICharacter;
	Texture2D* mTexCollectable;
	Texture2D* mTexAIEvil;
	Texture2D* mTexFloor;

	Sphere* mCharacterBounding;
	Sphere* mAIBounding;

	int m_iP1BallsCollected;
	int m_iAIBallsCollected;

};

