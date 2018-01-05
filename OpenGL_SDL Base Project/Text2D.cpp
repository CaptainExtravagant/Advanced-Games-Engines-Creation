#include "Text2D.h"
#include "../gl/glut.h"

Text2D::Text2D()
{
	InitText2D("");
}

Text2D::~Text2D()
{

}

void Text2D::PrintText(const char* text, int x, int y, int size)
{
	int length = strlen(text);

	vector <Vector2D> uvs;
	vector <Vector2D> vertices;

	for (unsigned int i = 0; i < length; i++)
	{
		Vector2D vertexUpLeft = Vector2D(x + i * size, y + size);
		Vector2D vertexUpRight = Vector2D(x + i * size + size, y + size);
		Vector2D vertexDownRight = Vector2D(x + i * size + size, y);
		Vector2D vertexDownLeft = Vector2D(x + i * size, y);

		vertices.push_back(vertexUpLeft);
		vertices.push_back(vertexDownLeft);
		vertices.push_back(vertexUpRight);

		vertices.push_back(vertexDownRight);
		vertices.push_back(vertexUpRight);
		vertices.push_back(vertexDownLeft);

		char character = text[i];
		float uvX = (character % 16) / 16.0f;
		float uvY = (character / 16) / 16.0f;

		Vector2D uvUpLeft = Vector2D(uvX, uvY);
		Vector2D uvUpRight = Vector2D(uvX + 1.0f / 16.0f, uvY);
		Vector2D uvDownRight = Vector2D(uvX + 1.0f / 16.0f, uvY + 1.0f / 16.0f);
		Vector2D uvDownLeft = Vector2D(uvX, uvY + 1.0f / 16.0f);

		uvs.push_back(uvUpLeft);
		uvs.push_back(uvDownLeft);
		uvs.push_back(uvUpRight);

		uvs.push_back(uvDownRight);
		uvs.push_back(uvUpRight);
		uvs.push_back(uvDownLeft);
	}
	/*
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2D()), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vector2D()), &uvs[0], GL_STATIC_DRAW);
	*/

	//Bind Shader
	
	//Bind Texture

	//1st Attribute Vertices
	
	//2nd Attribute Vertices


	

	//Draw Call
	


}

void Text2D::CleanUpText()
{

}

void Text2D::InitText2D(const char* texturePath)
{
	//Init texture
	textureID = 0;

	//Init VBO

	//Init Shader

	//Init Uniforms
}