#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <SDL.h>
#include "Commons.h"
#include "Constants.h"

class GameObject;

class BaseComponent {
public:
	BaseComponent(GameObject* object);
	~BaseComponent();

	GameObject* GetOwningObject();

protected:
	GameObject* parentObject;
};

#endif