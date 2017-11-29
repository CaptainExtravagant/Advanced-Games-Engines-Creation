#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Commons.h"
#include <vector>

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetPosition(Vector3D newPosition);
	void SetRotation(Vector3D newRotation);
	void SetScale(Vector3D newScale);

	Vector3D GetPosition();
	Vector3D GetRotation();
	Vector3D GetScale();

protected:
	Transform mTransform;
};

#endif