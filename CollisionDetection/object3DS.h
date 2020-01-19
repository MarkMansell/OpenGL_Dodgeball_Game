#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_

#include "Commons.h"
#include <string>
#include <Windows.h>
#include <gl/GLU.h>
using std::string;

class object3DS
{
public:
	object3DS(Vector3D startPosition, string modelFileName);
	~object3DS(){}

	void update(float deltaTime);
	void render();

	void SetRotation(float angle, float x, float y, float z);
	void SetTransform(float x, float y, float z);

	void SetTexture(GLuint _IDTex);

	Vector3D GetStartPos() const
	{
		return mposition;
	}

	//Load 3DS file
	void loadModel();
	Vector3D mgPosition;
	Vector3D mgRotation;

private:
	GLuint _TextureID;

	Vector3D mposition;
	Vector3D mrotation;

	float mrotationangle;

	char fileName[20];
	char textureName[20];	

	bool TextureSet;

	obj_type object;
};



#endif //_OBJECT3DS_h_