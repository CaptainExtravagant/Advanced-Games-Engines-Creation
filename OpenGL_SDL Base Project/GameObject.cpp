#include "GameObject.h"
#include "../gl/glut.h"
#include "OBJLoader.h"

GameObject::GameObject(Vector3D startPosition, string modelFileName)
{
	//Start position
	mTransform = Transform(startPosition, Vector3D(0, 0, 0), Vector3D(1, 1, 1));
	mQuatRotation = Quaternion();

	//Load mesh
	strcpy_s(fileName, modelFileName.c_str());
	LoadModel();
}

GameObject::~GameObject()
{
	children.clear();
	parent = NULL;
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

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->Render();
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(mTransform.position.x, mTransform.position.y, mTransform.position.z);

	glRotatef(mTransform.rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(mTransform.rotation.z, 0.0f, 0.0f, 1.0f);
	glRotatef(mTransform.rotation.x, 1.0f, 0.0f, 0.0f);

	//glRotatef(mQuatRotation.w, mQuatRotation.x, mQuatRotation.y, mQuatRotation.z);

	glScalef(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);

	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, 1);

	RenderModel();
		
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
	/*
	//Reset rotation if less than 0
	if (mTransform.rotation.x < 0)
	{
	mTransform.rotation.x += 360;
	}

	if (mTransform.rotation.y < 0)
	{
	mTransform.rotation.y += 360;
	}

	if (mTransform.rotation.z < 0)
	{
	mTransform.rotation.z += 360;
	}

	//Reset rotation if more than 360
	if (mTransform.rotation.x > 360)
	{
	mTransform.rotation.x -= 360;
	}

	if (mTransform.rotation.y > 360)
	{
	mTransform.rotation.y -= 360;
	}

	if (mTransform.rotation.z > 360)
	{
	mTransform.rotation.z -= 360;
	}
	*/

	mQuatRotation.FromEuler(mTransform.rotation.x, mTransform.rotation.y, mTransform.rotation.z);
}