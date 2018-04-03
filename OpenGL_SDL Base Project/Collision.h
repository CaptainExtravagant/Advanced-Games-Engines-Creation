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

class Collision {
public:
	static bool SphereSphereCollision(Sphere *s1, Sphere *s2) {
		Vector3D centre1 = s1->GetCentre();
		Vector3D centre2 = s2->GetCentre();
		float dx = centre2.x - centre1.x;
		float dy = centre2.y - centre1.y;
		float dz = centre2.z - centre1.z;

		float dSquared = dx*dx + dy*dy + dz *dz;

		float sumOfBoundingRadii = s1->GetBoundingRadius() + s2->GetBoundingRadius();

		float hasCollided = false;

		if (s1->IsEnabled() && s2->IsEnabled())
		{
			if (dSquared < (sumOfBoundingRadii * sumOfBoundingRadii)) {
				s1->SetCollided(true, s2->GetOwningObject());
				s2->SetCollided(true, s1->GetOwningObject());
				return true;
			}
		}
		return false;
	}
};
