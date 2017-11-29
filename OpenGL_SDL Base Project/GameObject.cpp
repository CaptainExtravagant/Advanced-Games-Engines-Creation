#include "GameObject.h"

GameObject::GameObject()
{
	mTransform = Transform(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));
}

GameObject::~GameObject()
{
	
}

void GameObject::SetPosition(Vector3D newPosition)
{
	mTransform.position = newPosition;
}

void GameObject::SetRotation(Vector3D newRotation)
{
	mTransform.rotation = newRotation;
}

void GameObject::SetScale(Vector3D newScale)
{
	mTransform.scale = newScale;
}

Vector3D GameObject::GetPosition()
{
	return mTransform.position;
}