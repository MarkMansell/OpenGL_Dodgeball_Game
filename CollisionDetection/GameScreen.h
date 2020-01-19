#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <glut.h>
#include <string>
#include "Texture.h"
#include "Sound.h"
#include "Commons.h"


using namespace std;

class GameScreenManager;


class GameScreen
{
public:
	GameScreen(GameScreenManager  * gsm);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void OutputLine(float x, float y, string text);

protected:
	SDL_Renderer* mRenderer;
	GameScreenManager * mManager;
	Vector3D mCameraPos;
	Vector3D mCameraLookAt;
};


#endif //_GAMESCREEN_H