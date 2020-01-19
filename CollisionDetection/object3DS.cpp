#include "object3DS.h"
#include "../gl/glut.h"
#include "3dsLoader.h"
#include "Texture.h"


object3DS::object3DS(Vector3D startPosition, string modelFileName)
{
	//Start Positon
	mposition = startPosition;

	//3DS file to lead.
	std::strcpy(fileName, modelFileName.c_str());
	loadModel();

	//Clear all the rotation floats
	mrotationangle = 0.0f;
	mrotation.x = 0.0f;
	mrotation.y = 0.0f;
	mrotation.z = 0.0f;
	TextureSet = false;


}

void object3DS::SetTexture(GLuint _IDTex)
{	
	_TextureID = _IDTex;

}

void object3DS::SetTransform(float x, float y, float z)
{
	mposition.x = x;
	mposition.y = y;
	mposition.z = z;
}

void object3DS::SetRotation(float angle, float x, float y, float z)
{
	mrotationangle = angle;
	mrotation.x = x;
	mrotation.y = y;
	mrotation.z = z;
}



void object3DS::loadModel()
{
	if (fileName[0] != '-')
	{
		Load3DS(&object, fileName);
	}
}


void object3DS::update(float deltaTime)
{
	//TODO: Move object here
	mposition.x += deltaTime; // deltaTime;
}

void object3DS::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPushMatrix();
	//glTranslatef(mposition.x, mposition.y, mposition.z);
	//glRotatef(mrotationangle, mrotation.x, mrotation.y, mrotation.z);

	glTranslatef(mgPosition.x, mgPosition.y, mgPosition.z);

	glBindTexture(GL_TEXTURE_2D, _TextureID); // We set the active texture
	
	
	glBegin(GL_TRIANGLES); //glBegin and glEnd delimit the vertices that define a primative (in our case triangles)
	
	for (int l_index = 0; l_index < object.polygons_qty; l_index++)
	{
		//FIRST VERTEX
		//Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u,object.mapcoord[object.polygon[l_index].a].v);
		//Coordinates of the first vertex
		glVertex3f(object.vertex[object.polygon[l_index].a].x, object.vertex[object.polygon[l_index].a].y, object.vertex[object.polygon[l_index].a].z);
		//SECOND VERTEX
		//Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u, object.mapcoord[object.polygon[l_index].b].v);
		//Coordinates of the second vertex
		glVertex3f(object.vertex[object.polygon[l_index].b].x, object.vertex[object.polygon[l_index].b].y, object.vertex[object.polygon[l_index].b].z);
		//THIRD VERTEX
		//Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u, object.mapcoord[object.polygon[l_index].c].v);
		//Coordinates of the second vertex
		glVertex3f(object.vertex[object.polygon[l_index].c].x, object.vertex[object.polygon[l_index].c].y, object.vertex[object.polygon[l_index].c].z);
	}
	
	glEnd();
	//glPopMatrix();
	glPolygonMode(GL_FRONT, GL_LINE);
}

