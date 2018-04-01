#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "BaseComponent.h"

class RigidBody : public BaseComponent
{
public:
	RigidBody(GameObject* owningObject) : BaseComponent(owningObject)
	{}

	bool gravityEnabled = true;
	bool shouldBounce = true;
	Vector3D acceleration = Vector3D(0, -1.0, 0);
	Vector3D gravityAcceleration = Vector3D(0, -GRAVITY_STRENGTH, 0);
	Vector3D velocity = Vector3D(0, 0, 0);

	void Update(float deltaTime, SDL_Event e)
	{
						
		parentObject->SetPosition(Vector3D(parentObject->GetPosition() + velocity*deltaTime + acceleration * (0.5 * deltaTime * deltaTime)));

		velocity += acceleration * deltaTime;
		velocity *= 0.98;

		if (parentObject->GetPosition().y <= 2)
		{
			velocity.y *= -restitution;
		}
	}

private:
	float restitution = 0.8f;
};

#endif