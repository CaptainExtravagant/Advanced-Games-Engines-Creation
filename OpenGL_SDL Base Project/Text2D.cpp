#include "Text2D.h"
#include "../gl/glut.h"

Text2D::Text2D(string inText, float x, float y)
{
	text = inText;
	position = Vector2D(x, y);

	PrintText();
}

Text2D::~Text2D()
{

}

void Text2D::PrintText()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Text2D::ClearText()
{
	text = "";
	PrintText();
}

void Text2D::UpdatePosition(float x, float y)
{
	position.x = x;
	position.y = y;

	PrintText();
}

void Text2D::UpdateText(string inText)
{
	text = inText;

	PrintText();
}

void Text2D::OutputLine()
{
	glRasterPos2f(position.x, position.y);
	for (unsigned int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}