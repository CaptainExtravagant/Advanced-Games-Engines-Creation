#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Vector3D startPosition, string modelFileName, string textureFileName) : GameObject(startPosition, modelFileName, textureFileName)
{
	movement = 4.0f;
	hits = 0;
	//SetScale(Vector3D(0.1f, 0.1f, 0.1f));
	mController = SDL_GameControllerOpen(controllerIndex);

	sphere = new Sphere(mTransform.position, 1.7f, this);
	components.push_back(sphere);
}

PlayerCharacter::~PlayerCharacter()
{
	SDL_GameControllerClose(mController);
	mController = NULL;
}

void PlayerCharacter::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
			//Keyboard Controls
		case SDLK_d:
			//Move Right
			xDir = 1;
			break;

		case SDLK_a:
			//Move Left
			xDir = -1;
			break;

		case SDLK_w:
			//Move Up
			yDir = -1;
			break;

		case SDLK_s:
			//Move Down
			yDir = 1;
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			xDir = 0;
			break;

		case SDLK_a:
			xDir = 0;
			break;

		case SDLK_w:
			yDir = 0;
			break;

		case SDLK_s:
			yDir = 0;
			break;
		}
		break;

		//Gamepad Controls
	case SDL_JOYAXISMOTION:
		
		if (e.jaxis.which == controllerIndex)
		{
			stickInput = Vector2D(
				SDL_GameControllerGetAxis(mController, SDL_GameControllerAxis(SDL_CONTROLLER_AXIS_LEFTX)),
				SDL_GameControllerGetAxis(mController, SDL_GameControllerAxis(SDL_CONTROLLER_AXIS_LEFTY)));

			if (stickInput.Magnitude() > pow(JOYSTICK_DEAD_ZONE, 2))
			{
				xDir = stickInput.x / JOYSTICK_MAX_AXIS;
				yDir = stickInput.y / JOYSTICK_MAX_AXIS;
			}
			else
			{
				xDir = 0;
				yDir = 0;
			}
		}
		break;
	}

	if (GetPosition().x + ((xDir * movement) * deltaTime) < -14.3f)
	{
		xDir = 0;
	}

	if (GetPosition().z + ((yDir * movement) * deltaTime) < -6.3f || GetPosition().z + ((yDir * movement) * deltaTime) > 6.3f)
	{
		yDir = 0;
	}

	SetPosition(Vector3D(GetPosition().x + ((xDir * movement) * deltaTime), GetPosition().y, GetPosition().z + ((yDir * movement) * deltaTime)));
	
	sphere->SetCollided(false, NULL);
	sphere->Update(mTransform.position);
}

void PlayerCharacter::HitBall()
{
	hits += 1;
}