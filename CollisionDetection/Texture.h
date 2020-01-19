#ifndef _Texure2D_H
#include <Windows.h>
#include <gl/GLU.h>

class Texture2D
{
private:
	GLuint _ID;
	int _width, _height;

public:
	Texture2D();
	~Texture2D();

	bool Load(char*, int width, int height);

	GLuint GetID() const{ return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
};


#endif // !_Texure2D_H
