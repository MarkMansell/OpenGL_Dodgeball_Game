#include "Texture.h"
#include <iostream>
#include <fstream>

using namespace::std;

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char*  tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); // Seek to end of file
	fileSize = (int)inFile.tellg(); // Get current position in file - The End, this gives us total file size
	tempTextureData = new char[fileSize]; //Create a new array to store data
	inFile.seekg(0, ios::beg); //Seek back to beginning of file
	inFile.read(tempTextureData, fileSize); // Read in all the data in one go
	inFile.close();

	cout << path << " Loaded." << endl;

	glGenTextures(1, &_ID); //Get next texture Id
	glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture to the ID



	//Set some parameters so it renders correctly
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);	

	delete[] tempTextureData; // Clear up the data - We don't need this anymore

	return	true;
}