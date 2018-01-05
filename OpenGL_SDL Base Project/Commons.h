#pragma once
#include <math.h>

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
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
	
	float Magnitude()
	{
		float magnitude;
		magnitude = pow(x, 2) + pow(y, 2);
		return magnitude;
	}

	Vector2D Normalise()
	{
		Vector2D normal;
		normal = Vector2D(x / Magnitude(), y / Magnitude());
		return normal;
	}

	float DotProduct(Vector2D point1, Vector2D point2)
	{
		float dot;
		dot = (point1.x * point2.x) + (point1.y * point2.y);
		return dot;
	}

	float DotProduct(Vector2D point1, Vector2D point2, float alpha)
	{
		float dot;
		dot = point1.Magnitude() * point2.Magnitude() * cos(alpha);
		return dot;
	}

	Vector2D operator* (float scalar)
	{
		return Vector2D(x * scalar, y*scalar);
	}

	Vector2D operator+ (const Vector2D& other)
	{
		return Vector2D(x + other.x, y + other.y);
	}

	Vector2D operator+= (const Vector2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2D operator-= (const Vector2D& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2D operator= (const Vector2D& other)
	{
		x = other.x;
		y = other.y;
		return *this;
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

	float Magnitude()
	{
		float magnitude;

		magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

		return magnitude;
	}

	Vector3D Normalise()
	{
		float magnitude = Magnitude();
		Vector3D normal;

		normal = Vector3D(x / magnitude, y / magnitude, z / magnitude);

		return normal;
	}

	float DotProduct(Vector3D point1, Vector3D point2)
	{
		float dot;
		dot = (point1.x * point2.x) + (point1.y * point2.y) + (point1.z * point2.z);
		return dot;
	}

	float DotProduct(Vector3D point1, Vector3D point2, float alpha)
	{
		float dot;
		dot = point1.Magnitude() * point2.Magnitude() * cos(alpha);
		return dot;
	}

	Vector3D CrossProduct(Vector3D point1, Vector3D point2)
	{
		Vector3D cross = Vector3D(
			(point1.y*point2.z) - (point1.z*point2.y),
			(point1.z*point2.x) - (point1.x*point2.z),
			(point1.x*point2.y) - (point1.y*point2.x));

		return cross;
	}

	Vector3D RotateAroundAxis(float angle, Vector3D axis)
	{
		Vector3D newTransform;
		float c = cos(angle);
		float s = sin(angle);

		newTransform = (Vector3D(
			((c + (1-c) * pow(axis.x, 2)) + ((1 - c) * axis.x * axis.y - (s * axis.z)) + ((1-c) * axis.x * axis.z + (s*axis.y))),
			(((1-c) * axis.x * axis.y + (s * axis.z)) + (c + (1-c) * pow(axis.y, 2)) + ((1-c) * axis.y * axis.z - (s*axis.x))),
			(((1-c) * axis.x * axis.z - (s*axis.y)) + ((1-c) * axis.y * axis.z + (s*axis.x)) + (c + (1-c) * pow(axis.z, 2)))
		));

		return newTransform;
	}

	Vector3D operator* (float scalar)
	{
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}

	Vector3D operator+ (const Vector3D& other)
	{
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

	Vector3D operator+= (const Vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3D operator-=(const Vector3D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3D operator= (const Vector3D& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}
};

struct Transform {

	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	Transform()
	{
		position = Vector3D(0, 0, 0);
		rotation = Vector3D(0, 0, 0);
		scale = Vector3D(0, 0, 0);
	}

	Transform(Vector3D initialPosition, Vector3D initialRotation, Vector3D initialScale)
	{
		position = initialPosition;
		rotation = initialRotation;
		scale = initialScale;
	}

	void AddPosition(Vector3D vectorToAdd)
	{
		position += vectorToAdd;
	}

	void AddScale(Vector3D scaleToAdd)
	{
		scale += scaleToAdd;
	}

};

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		//Unit Quaternion value. No rotation
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	Quaternion(float initialX, float initialY, float initialZ, float initialW)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
		w = initialW;
	}

	float Magnitude()
	{
		float magnitude;

		magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));

		return magnitude;
	}

	Quaternion Normalise()
	{
		float magnitude = Magnitude();

		Quaternion normalised(x / magnitude, y /magnitude, z / magnitude, w / magnitude);

		return normalised;
	}

	Quaternion Inverse()
	{
		return Quaternion(-x, -y, -z, w);
	}

	void FromEuler(float pitch, float yaw, float roll)
	{
		//X
		float cx = cos(pitch / 2.0f);
		float sx = sin(pitch / 2.0f);

		//Y
		float cy = cos(yaw / 2.0f);
		float sy = sin(yaw / 2.0f);
		
		//Z
		float cz = cos(roll / 2.0f);
		float sz = sin(roll / 2.0f);

		w = cx * cy * cz + sx * sy * sz;
		x = cx * sy * cz - sx * cy * sz;
		y = cx * cy * sz + sx * sy * sz;
		z = sx * cy * cz - cx * sy * sz;
	}

	void GetAxisAngle(Vector3D* v, float* angle)
	{
		float scale = sqrt(x * x + y * y + z * z);
		v->x = x / scale;
		v->y = y / scale;
		v->z = z / scale;

		*angle = acos(w) * 2.0f;
	}

	float Scale()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3D ToEuler()
	{
		Vector3D euler;

		//roll (x axis)
		float sinr = 2.0f * (w * x + y * z);
		float cosr = 1.0f - 2.0f * (x * x + y * y);
		euler.x = atan2f(sinr, cosr);

		//pitch (y axis)
		float sinp = 2.0f * (w * y - z * x);
		if (fabs(sinp) >= 1)
			euler.y = copysign(3.14 / 2, sinp); //use 90 degrees if out of range
		else
			euler.y = asin(sinp);

		//yaw (z axis)
		float siny = 2.0f * (w * z + x * y);
		float cosy = 1.0f - 2.0f * (y * y + z * z);
		euler.z = atan2f(siny, cosy);

		return euler;
	}

	Quaternion operator* (Quaternion q2)
	{
		Quaternion q3(w * q2.x + x * q2.w + y * q2.z - z * q2.y,
			w * q2.y + y * q2.w + z * q2.x - x * q2.z,
			w * q2.z + z * q2.w + x * q2.y - y * q2.x,
			w * q2.w - x * q2.x - y * q2.y - z * q2.z);

		return q3;
	}

	Vector3D operator* (Vector3D v)
	{
		Vector3D vn(v);
		vn.Normalise();

		Quaternion vecQuat, resQuat;

		vecQuat.x = vn.x; vecQuat.y = vn.y; vecQuat.z = vn.z; vecQuat.w = 0.0f;
		resQuat = vecQuat * Inverse(); resQuat = *this * resQuat;

		return(Vector3D(resQuat.x, resQuat.y, resQuat.z));

	}
};

struct lighting {
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

struct TexCoord {
	float u;
	float v;
};

//OBJ Loader type details
#define MAX_VERTICES 30000
#define MAX_POLYGONS 30000

//The polygon triangle
struct Triangle {
	int a;
	int b;
	int c;
};

//Object type
typedef struct
{
	char name[20];
	int vertices_qty;
	int polygons_qty;
	int normals_qty;
	Vector3D vertex[MAX_VERTICES];
	Vector3D normal[MAX_VERTICES];
	Triangle polygon[MAX_POLYGONS];
	TexCoord texcoord[MAX_VERTICES];
	int id_texture;
} obj_type, *obj_type_ptr;