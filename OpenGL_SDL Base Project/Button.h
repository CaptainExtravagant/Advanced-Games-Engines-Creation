#ifndef BUTTON_H
#define BUTTON_H

#include "Text2D.h"
#include <SDL.h>

class Button {

public:
	Button(Vector2D position, string text);
	~Button();
	bool IsFocused();

	void ChangeFocused(int position);
	void SetNeighborButton(Button* newButton, int position);
	void UpdateText(string text);
	void UpdatePosition(Vector2D newPosition);
	void UpdatePosition(float x, float y);

	void Render();

protected:
	bool isFocused;

	void SetFocus();

	Button* mAboveButton;
	Button* mBelowButton;
	Button* mLeftButton;
	Button* mRightButton;

	Text2D* mButtonText;
	string baseText;

	Vector2D position;

};
#endif