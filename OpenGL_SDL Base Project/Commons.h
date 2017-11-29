#pragma once

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