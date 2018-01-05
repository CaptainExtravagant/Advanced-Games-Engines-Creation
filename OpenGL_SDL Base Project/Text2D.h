#ifndef TEXT2D_H
#define TEXT2D_H

#include <string>
#include "Commons.h"
#include <vector>

using namespace std;

class Text2D
{
public:

	Text2D();
	~Text2D();

	void PrintText(const char* text, int x, int y, int size);
	void CleanUpText();

	int textureID;
	int vertexBufferID;
	int uvBufferID;
	int shaderID;
	int uniformID;

private:
	void InitText2D(const char* texturePath);
};

#endif