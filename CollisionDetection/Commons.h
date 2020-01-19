 #pragma once

//3DS Max Object type Details
#define MAX_VERTICES 15000
#define MAX_POLYGONS 15000
#include <math.h>

//Our vertex type
typedef struct
{
	float x, y, z;
} vertex_type;

//The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct
{
	int a, b, c;
} polygon_type;

//The mapcoord type, 2 texture coordinates for each vertex
typedef struct
{
	float u, v;
} mapcoord_type;

typedef struct
{
	int a, b, c;
} UV_index;

//The object type
typedef struct
{
	char name[20];

	int vertice_qty;
	int polygons_qty;
	int id_texture;

	vertex_type vertex[MAX_VERTICES];
	polygon_type polygon[MAX_POLYGONS];
	mapcoord_type mapcoord[MAX_VERTICES];
	UV_index UV_Index[MAX_POLYGONS];

}obj_type, *obj_type_ptr;

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES,
	SCREEN_L1_Complete,
	SCREEN_L2_Complete,
	SCREEN_INFO
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width  = initialWidth;
		height = initialHeight;
	}
};

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3D(float initialX, float initialY, float initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}

	Vector3D operator+(const Vector3D b)
	{
		Vector3D result;
		result.x = x + b.x;
		result.y = y + b.y;
		result.z = z + b.z;
		return result;
	}
	Vector3D operator-(const Vector3D b)
	{
		Vector3D result;
		result.x = x - b.x;
		result.y = y - b.y;
		result.z = z - b.z;
		return result;
	}
	Vector3D operator*(const Vector3D b)
	{
		Vector3D result;
		result.x = x * b.x;
		result.y = y * b.y;
		result.z = z * b.z;
		return result;
	}
	Vector3D operator* (const float b)
	{
		Vector3D result;
		result.x = x * b;
		result.y = y * b;
		result.z = z * b;
		return result;

	}
	Vector3D operator+=(const Vector3D b)
	{
		Vector3D result;
		x = x + b.x;
		y = y + b.y;
		z = z + b.z;
		return result;
	}
	Vector3D operator*=(const Vector3D b)
	{
		Vector3D result;
		x = x * b.x;
		y = y * b.y;
		z = z * b.z;
		return result;
	}
	void Vector3D::normalise()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
	}
	float Vector3D::length()
	{
		return sqrt(x*x + y*y + z*z);
	}
	
};

struct lighting{
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

struct material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};

enum CameraType
{
	CAMERA_PERSPECTIVE,
	CAMERA_ORTHO
};


