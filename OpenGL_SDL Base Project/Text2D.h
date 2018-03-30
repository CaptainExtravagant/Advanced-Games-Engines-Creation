#ifndef TEXT2D_H
#define TEXT2D_H

#include <string>
#include "Commons.h"
#include <vector>

using namespace std;

class Text2D
{
public:

	Text2D(string inText, float x, float y);
	~Text2D();

	void PrintText();
	void ClearText();
	void UpdateText(string inText);
	void UpdatePosition(float x, float y);

protected:
	void OutputLine();

private:
	Vector2D position;
	string text;

};

#endif