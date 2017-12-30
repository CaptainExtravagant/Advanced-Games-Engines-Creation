#include "GameObject.h"
#include "../gl/glut.h"
#include "OBJLoader.h"

GameObject::GameObject(Vector3D startPosition, string modelFileName)
{
	//Start position
	mTransform = Transform(startPosition, Vector3D(0, 0, 0), Vector3D(1, 1, 1));

	//Load mesh
	strcpy_s(fileName, modelFileName.c_str());
	LoadModel();
}

GameObject::~GameObject()
{
	
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

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(mTransform.position.x, mTransform.position.y, mTransform.position.z);

	glRotatef(mTransform.rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(mTransform.rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(mTransform.rotation.z, 0.0f, 0.0f, 1.0f);



	glScalef(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);

	//Bind Texture

	glBegin(GL_TRIANGLES);

	for (int l_index = 0; l_index < object.polygons_qty; l_index++)
	{
		//First vertex
		//glTexCoord2f(object.texcoord[object.polygon[l_index].a].u,
			//object.texcoord[object.polygon[l_index].a].v);

		/*
		glNormal3f(object.normal[object.polygon[l_index].a].x,
			object.normal[object.polygon[l_index].a].y,
			object.normal[object.polygon[l_index].a].z);
			*/
		glVertex3f(object.vertex[object.polygon[l_index].a].x,
			object.vertex[object.polygon[l_index].a].y,
			object.vertex[object.polygon[l_index].a].z);

		//Second vertex
		//glTexCoord2f(object.texcoord[object.polygon[l_index].b].u,
			//object.texcoord[object.polygon[l_index].b].v);
		/*
		glNormal3f(object.normal[object.polygon[l_index].b].x,
			object.normal[object.polygon[l_index].b].y,
			object.normal[object.polygon[l_index].b].z);
			*/
		glVertex3f(object.vertex[object.polygon[l_index].b].x,
			object.vertex[object.polygon[l_index].b].y,
			object.vertex[object.polygon[l_index].b].z);

		//Third vertex
		//glTexCoord2f(object.texcoord[object.polygon[l_index].c].u,
			//object.texcoord[object.polygon[l_index].c].v);
		/*
		glNormal3f(object.normal[object.polygon[l_index].c].x,
			object.normal[object.polygon[l_index].c].y,
			object.normal[object.polygon[l_index].c].z);
			*/
		glVertex3f(object.vertex[object.polygon[l_index].c].x,
			object.vertex[object.polygon[l_index].c].y,
			object.vertex[object.polygon[l_index].c].z);
	}

	glEnd();
	
	glPopMatrix();
}

void GameObject::Update(float deltaTime, SDL_Event e)
{
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
}