#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include <vector>
#include "Teapot.h"
#include <string>
//#include "Texture.h"
#include "object3DS.h"
#include "InputManager.h"
#include "Collision.h"
using namespace std;


class GameScreenLevel1 : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1(GameScreenManager* gsm);
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void		DisplayHUD(string text, float x, float y);
	int GetCollisionCount(){ return mCollisionNum; }
	void CountCollision(Teapot * collided);
	void CharacterController(object3DS* player, float deltatime);
	virtual void AddCollision() { mCollisionNum++; }
	void SetMaterial();
	void SetLight();

protected:
	void EndOfLevel(bool failed, float time, int hitcount);
	//--------------------------------------------------------------------------------------------------
private:

	InputManager* mInput;
	Sphere* mCharacterSphere;
	Sphere* mLevelEndPoint;

	Sound* mSoundDeath;
	Sound* mSoundLevelComplete;

	object3DS* mCourt;
	object3DS* mCourtWalls;
	object3DS* mObj_Octopus;
	object3DS* mCharacter;

	bool mHasLevelEnded;

	float mCurrentTime;
	vector<Teapot *> theTeapots;
	int mCollisionCount;
	int mCollisionNum;
	bool mcollided;
	Texture2D* mTexCourt;
	Texture2D* mTexCourtWalls;
	Texture2D* mTexCharacter;

};


#endif //_GAMESCREENLEVEL1_H