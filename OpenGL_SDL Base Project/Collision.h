#pragma once
// Collision - library of functions and classes for collision detection
#include "Commons.h"
#include "BaseComponent.h"


class Sphere : public BaseComponent {
public:
	Sphere(Vector3D c, float r, GameObject* owningObject) : BaseComponent(owningObject) { centre = c; radius = r; collided = false; }
	float GetBoundingRadius() const { return radius; }
	Vector3D GetCentre() { return centre; }
	void Update(Vector3D newPos) { centre = newPos; }
	void SetCollided(bool c, GameObject* colObject) { collided = c; collidedObject = colObject;}
	bool GetCollided() { return collided; }
	GameObject* GetCollidedObject() { return collidedObject; }
	bool IsEnabled() { return enabled; }
	void SetEnabled(bool isEnabled) { enabled = isEnabled; }
private:
	Vector3D centre;
	float radius;
	bool collided;
	GameObject* collidedObject;
	bool enabled = true;
};

class Box : public BaseComponent {
public:
	Box(Vector3D c, float w, float h, float d, GameObject* owningObject) : BaseComponent(owningObject) { centre = c; width = w; height = h; depth = d; collided = false; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	float GetDepth() { return depth; }
	Vector3D GetCentre() { return centre; }

	void Update(Vector3D newPos) { centre = newPos; }
	void SetCollided(bool c, GameObject* object) { collided = c; collidedObject = object; }
	bool GetCollided() { return collided; }
	GameObject* GetCollidedObject() { return collidedObject; }
	bool IsEnabled() { return enabled; }
	void SetEnabled(bool isEnabled) { enabled = isEnabled; }
private:
	Vector3D centre;
	float width;
	float height;
	float depth;
	bool collided;
	GameObject* collidedObject;
	bool enabled = true;
};

class Collision {
public:
	static bool SphereSphereCollision(Sphere *s1, Sphere *s2) {

		if (s1->IsEnabled() && s2->IsEnabled())
		{
			Vector3D centre1 = s1->GetCentre();
			Vector3D centre2 = s2->GetCentre();
			float dx = centre2.x - centre1.x;
			float dy = centre2.y - centre1.y;
			float dz = centre2.z - centre1.z;

			float dSquared = dx*dx + dy*dy + dz *dz;

			float sumOfBoundingRadii = s1->GetBoundingRadius() + s2->GetBoundingRadius();

			float hasCollided = false;

				if (dSquared < (sumOfBoundingRadii * sumOfBoundingRadii)) {
					s1->SetCollided(true, s2->GetOwningObject());
					s2->SetCollided(true, s1->GetOwningObject());
					return true;
				}
		}
		return false;
	}

	static bool SphereBoxCollision(Sphere* s, Box* b)
	{
		if (s->IsEnabled() && b->IsEnabled())
		{
			Vector3D centreS = s->GetCentre();
			float radius = s->GetBoundingRadius();
			float cMaxX = centreS.x + radius;
			float cMinX = centreS.x - radius;
			float cMaxY = centreS.y + radius;
			float cMinY = centreS.y - radius;
			float cMaxZ = centreS.z + radius;
			float cMinZ = centreS.z - radius;
			
			Vector3D centreB = b->GetCentre();
			float w = b->GetWidth();
			float maxX = centreB.x - (w / 2);
			float minX = centreB.x + (w / 2);
			float h = b->GetHeight();
			float maxY = centreB.y - (h / 2);
			float minY = centreB.y + (h / 2);
			float d = b->GetDepth();
			float maxZ = centreB.z - (d / 2);
			float minZ = centreB.z + (d / 2);

			bool cX = false;
			bool cY = false;
			bool cZ = false;

			if (maxX > cMinX && minX < cMaxX)
			{
				cX = true;
			}
			if (maxY > cMinY && minY < cMaxY)
			{
				cY = true;
			}
			if (maxZ > cMinZ && minZ < cMaxZ)
			{
				cZ = true;
			}
			if (cX && cY && cZ)
				return true;
		}
		return false;
	}

	static bool BoxBoxCollision(Box* b1, Box* b2)
	{
		if (b1->IsEnabled() && b2->IsEnabled())
		{
			Vector3D centre1 = b1->GetCentre();
			Vector3D centre2 = b2->GetCentre();

			float w1 = b1->GetWidth();
			float minX1 = centre1.x - (w1 / 2);
			float maxX1 = centre1.x + (w1 / 2);

			float w2 = b2->GetWidth();
			float minX2 = centre2.x - (w2 / 2);
			float maxX2 = centre2.x + (w2 / 2);

			float h1 = b1->GetHeight();
			float minY1 = centre1.y - (h1 / 2);
			float maxY1 = centre1.y + (h1 / 2);

			float h2 = b2->GetHeight();
			float minY2 = centre2.y - (h2 / 2);
			float maxY2 = centre2.y + (h2 / 2);

			float d1 = b1->GetDepth();
			float minZ1 = centre1.z - (d1 / 2);
			float maxZ1 = centre1.z + (d1 / 2);

			float d2 = b2->GetDepth();
			float minZ2 = centre2.z - (d2 / 2);
			float maxZ2 = centre2.z + (d2 / 2);

			bool xCollision = false;
			bool yCollision = false;
			bool zCollision = false;

			if (maxX1 > minX2 && minX1 < maxX2)
			{
				xCollision = true;
			}

			if (maxY1 > minY2 && minY1 < maxY2)
			{
				yCollision = true;
			}

			if (maxZ1 > minZ2 && minZ1 < maxZ2)
			{
				zCollision = true;
			}

			if (xCollision&&yCollision&&zCollision)
			{
				return true;
			}
		}

		return false;
	}

	static bool SphereLineCollision(Sphere* s, Vector3D lineStart, Vector3D lineEnd)
	{
		if (s->IsEnabled())
		{
			float t;
			Vector3D pt;
			float d;

			float radius = s->GetBoundingRadius();
			radius *= radius;

			Vector3D lineDirection = (lineEnd - lineStart);
			float lineLength = lineDirection.Magnitude();

			float a = (lineDirection.x * lineDirection.x) + (lineDirection.y * lineDirection.y) + (lineDirection.z * lineDirection.z);
			float b = 2 * lineStart.DotProduct(lineDirection);
			float c = lineStart.DotProduct(lineStart) - radius;

			d = (b*b) - 4 * (a * c);

			if (d > 0)
			{
				//Collision made
				t = ((-b) - sqrt(d)) / (2 * a);
				if (t > lineLength)
				{
					return false;
				}
				//First point of collision
				pt = lineStart + (lineDirection * t);
				return true;
			}
		}
		return false;
	}

	static bool BoxLineCollision(Box* b, Vector3D lineStart, Vector3D lineEnd)
	{
		if (b->IsEnabled())
		{
			Vector3D centre = b->GetCentre();
			float minX = centre.x - (b->GetWidth() / 2);
			float maxX = centre.x + (b->GetWidth() / 2);

			float minY = centre.y - (b->GetHeight() / 2);
			float maxY = centre.y + (b->GetHeight() / 2);

			float minZ = centre.z - (b->GetDepth() / 2);
			float maxZ = centre.z + (b->GetDepth() / 2);

			Vector3D lineDirection = (lineEnd - lineStart).Normalise();
			float lineLength = (lineEnd - lineStart).Magnitude();

			float t;
			Vector3D pt;

			//Test X
			if (lineEnd.x > minX)
			{
				//Test min
				t = (minX - lineStart.x) / lineDirection.x;
				pt = lineStart + (lineDirection * t);

				if (t > lineLength)
				{
					return false;
				}

				if ((pt.y >= minY && pt.y <= maxY) &&
					(pt.z >= minZ && pt.z <= maxZ))
				{
					return true;
				}
			}
			else if (lineEnd.x < maxX)
			{
				//Test max
				t = (maxX - lineStart.x) / lineDirection.x;
				pt = lineStart + (lineDirection * t);

				if (t > lineLength)
				{
					return false;
				}

				if ((pt.y >= minY && pt.y <= maxY) &&
					(pt.z >= minZ && pt.z <= maxZ))
				{
					return true;
				}
			}

			//Test Y
			if (lineEnd.y > minY)
			{
				//Test min
				t = (minY - lineStart.y) / lineDirection.y;
				pt = lineStart + (lineDirection * t);

				if (t > lineLength)
				{
					return false;
				}

				if ((pt.x >= minX && pt.x <= maxX) &&
					(pt.z >= minZ && pt.z <= maxZ))
				{
					return true;
				}
			}
			else if (lineEnd.y < maxY)
			{
				//Test max
				t = (maxY - lineStart.y) / lineDirection.y;
				pt = lineStart + (lineDirection * t);

				if (t > lineLength)
				{
					return false;
				}

				if ((pt.x >= minX && pt.x <= maxX) &&
					(pt.z >= minZ && pt.z <= maxZ))
				{
					return true;
				}
			}

			//Test Z
			if (lineEnd.z > minZ)
			{
				//Test min
				t = (minZ - lineStart.z) / lineDirection.z;
				pt = lineStart + (lineDirection * t);

				if (t > lineLength)
				{
					return false;
				}

				if ((pt.x >= minX && pt.x <= maxX) &&
					(pt.y >= minY && pt.y <= maxY))
				{
					return true;
				}
			}
			else if (lineEnd.z < maxZ)
			{
				//Test max
				t = (maxZ - lineStart.z) / lineDirection.z;
				pt = lineStart + (lineDirection * t);

				if (t > lineLength)
				{
					return false;
				}

				if ((pt.x >= minX && pt.x <= maxX) &&
					(pt.y >= minY && pt.y <= maxY))
				{
					return true;
				}
			}


		}
		return false;
	}
};
