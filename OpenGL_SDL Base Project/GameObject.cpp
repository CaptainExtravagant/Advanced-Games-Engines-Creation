#include "GameObject.h"
#include "../gl/glut.h"
#include "OBJLoader.h"

GameObject::GameObject(Vector3D startPosition, string modelFileName, string textureFileName)
{
	//Start position
	mTransform = Transform(startPosition, Vector3D(270, 0, 0), Vector3D(1, 1, 1));
	mQuatRotation = Quaternion();

	//Load mesh
	strcpy_s(fileName, modelFileName.c_str());
	strcpy_s(textureName, textureFileName.c_str());

	LoadModel();
	LoadTexture();
}

GameObject::~GameObject()
{
	children.clear();
	parent = NULL;
}

template<class T>
BaseComponent* GameObject::GetComponent()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if ((T)components[i])
			return components[i];
	}
}

template<class T>
BaseComponent* GameObject::GetComponentInChildren()
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]->GetComponent<T>())
			return children[i]->GetComponent<T>();
	}
}

template<class T>
vector<BaseComponent*> GameObject::GetComponentsInChildren()
{
	vector<BaseComponent*> componentVector;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]->GetComponent<T>())
			componentVector.push_back(children[i]->GetComponent<T>());
	}

	return componentVector;
}

void GameObject::SetParent(GameObject* newParent)
{
	parent = newParent;
	parent->AddChild(this);
}

void GameObject::AddChild(GameObject* newChild)
{
	children.push_back(newChild);
}

vector<GameObject*> GameObject::GetChildren()
{
	return children;
}

GameObject* GameObject::GetParent()
{
	if (parent != NULL)
		return parent;
	else
		return NULL;
}

GameObject* GameObject::GetChild(int index)
{
	if (children[index] != NULL)
		return children[index];
	else
		return NULL;
}

void GameObject::LoadModel()
{
	if (fileName[0] != '---')
		LoadOBJ(fileName, &object);
}

void GameObject::LoadTexture()
{
	texture = new Texture2D();
	texture->Load(textureName, 512, 512);
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

Vector3D GameObject::GetRotation()
{
	return mTransform.rotation;
}

Vector3D GameObject::GetScale()
{
	return mTransform.scale;
}

void GameObject::Render()
{
	glPushMatrix();


	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(mTransform.position.x, mTransform.position.y, mTransform.position.z);

	glRotatef(mTransform.rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(mTransform.rotation.z, 0.0f, 0.0f, 1.0f);
	glRotatef(mTransform.rotation.x, 1.0f, 0.0f, 0.0f);

	//glRotatef(mQuatRotation.w, mQuatRotation.x, mQuatRotation.y, mQuatRotation.z);

	glScalef(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);

	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	RenderModel();

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->Render();
	}
		
	glPopMatrix();
}

void GameObject::RenderModel()
{

	glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index < object.polygons_qty; l_index++)
	{

		//First vertex
		glTexCoord2f(object.texcoord[object.uv[l_index].a - 1].u,
			object.texcoord[object.uv[l_index].a - 1].v);

		glNormal3f(object.normal[object.normals[l_index].a - 1].x,
			object.normal[object.normals[l_index].a - 1].y,
			object.normal[object.normals[l_index].a - 1].z);

		glVertex3f(object.vertex[object.polygon[l_index].a - 1].x,
			object.vertex[object.polygon[l_index].a - 1].y,
			object.vertex[object.polygon[l_index].a - 1].z);

		//Second vertex
		glTexCoord2f(object.texcoord[object.uv[l_index].b - 1].u,
			object.texcoord[object.uv[l_index].b - 1].v);

		glNormal3f(object.normal[object.normals[l_index].b - 1].x,
			object.normal[object.normals[l_index].b - 1].y,
			object.normal[object.normals[l_index].b - 1].z);

		glVertex3f(object.vertex[object.polygon[l_index].b - 1].x,
			object.vertex[object.polygon[l_index].b - 1].y,
			object.vertex[object.polygon[l_index].b - 1].z);

		//Third vertex
		glTexCoord2f(object.texcoord[object.uv[l_index].c - 1].u,
			object.texcoord[object.uv[l_index].c - 1].v);

		glNormal3f(object.normal[object.normals[l_index].c - 1].x,
			object.normal[object.normals[l_index].c - 1].y,
			object.normal[object.normals[l_index].c - 1].z);

		glVertex3f(object.vertex[object.polygon[l_index].c - 1].x,
			object.vertex[object.polygon[l_index].c - 1].y,
			object.vertex[object.polygon[l_index].c - 1].z);

	}

	glEnd();
}

void GameObject::Update(float deltaTime, SDL_Event e)
{

}