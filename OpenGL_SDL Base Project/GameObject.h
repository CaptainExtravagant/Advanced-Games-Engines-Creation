#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Commons.h"
#include "BaseComponent.h"
#include "Texture2D.h"
#include <vector>
#include <SDL.h>

using namespace std;

class GameObject
{
public:
	GameObject(Vector3D startPosition, string modelFileName, string textureFileName);
	~GameObject();

	void SetPosition(Vector3D newPosition);
	void SetRotation(Vector3D newRotation);
	void SetScale(Vector3D newScale);

	void LoadModel();
	void LoadTexture();

	Vector3D GetPosition();
	Vector3D GetRotation();
	Vector3D GetScale();

	virtual void Render();
	void RenderModel();
	virtual void Update(float deltaTime, SDL_Event e);
	
	Transform mTransform;
	Quaternion mQuatRotation;

	GameObject* GetParent();
	GameObject* GetChild(int index);
	void SetParent(GameObject* parentObject);
	void AddChild(GameObject* newChild);
	vector<GameObject*> GetChildren();

	template<class T>
	BaseComponent* GetComponent();

	template<class T>
	BaseComponent* GetComponentInChildren();

	template<class T>
	vector<BaseComponent*> GetComponentsInChildren();

private:
	char fileName[20];
	char textureName[30];

	obj_type object;
	Texture2D texture;
	
	GameObject* parent;
	vector<GameObject*> children;
	vector<BaseComponent*> components;

	void SetMaterial();
};

#endif