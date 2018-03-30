#include "Button.h"

Button::Button(Vector2D position, string text)
{
	mButtonText = new Text2D(text, position.x, position.y);

	UpdatePosition(position);
	UpdateText(text);
}

Button::~Button()
{

}

void Button::UpdateText(string text)
{
	baseText = text;
	mButtonText->UpdateText(baseText);
}

void Button::UpdatePosition(Vector2D newPosition)
{
	position = newPosition;
	mButtonText->UpdatePosition(position.x, position.y);
}

void Button::UpdatePosition(float x, float y)
{
	position.x = x;
	position.y = y;
	mButtonText->UpdatePosition(position.x, position.y);
}

void Button::Render()
{
	mButtonText->PrintText();
}

bool Button::IsFocused()
{
	return isFocused;
}

void Button::SetFocus()
{
	isFocused = true;
	mButtonText->UpdateText(">> " + baseText + " <<");
}

void Button::SetNeighborButton(Button* newButton, int position)
{
	switch (position)
	{
	case 0:
		mAboveButton = newButton;
		break;

	case 1:
		mBelowButton = newButton;
		break;

	case 2:
		mRightButton = newButton;
		break;

	case 3:
		mLeftButton = newButton;
		break;

	default:
		break;
	}
}

void Button::ChangeFocused(int position)
{
	switch (position)
	{
	case 0:
		if (mAboveButton != NULL)
		{
			mAboveButton->SetFocus();
			mButtonText->UpdateText(baseText);
			isFocused = false;
		}
		break;

	case 1:
		if (mBelowButton != NULL)
		{
			mBelowButton->SetFocus();
			mButtonText->UpdateText(baseText);
			isFocused = false;
		}
		break;

	case 2:
		if (mRightButton != NULL)
		{
			mRightButton->SetFocus();
			mButtonText->UpdateText(baseText);
			isFocused = false;
		}
		break;

	case 3:
		if (mLeftButton != NULL)
		{
			mLeftButton->SetFocus();
			mButtonText->UpdateText(baseText);
			isFocused = false;
		}
		break;
		
	default:

		break;
	}
}