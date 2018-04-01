#include "BaseComponent.h"
#include "GameObject.h"

BaseComponent::BaseComponent(GameObject* object)
{
	parentObject = object;
}

BaseComponent::~BaseComponent()
{

}

GameObject* BaseComponent::GetOwningObject()
{
	return parentObject;
}