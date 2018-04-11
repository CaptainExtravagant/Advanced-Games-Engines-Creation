#include "Level2Player.h"
#include "../gl/glut.h"
#include <iostream>
#include "CharacterManager.h"
#include "Level2Enemy.h"

Level2Player::Level2Player(int playerIndex, Vector3D startPosition, string modelName, string textureName, CharacterManager* manager) : GameObject(startPosition, modelName, textureName)
{
	mManager = manager;
	movement = 6.0f;
	controllerIndex = playerIndex;

	if (SDL_NumJoysticks() > controllerIndex)
	{
		mController = SDL_GameControllerOpen(controllerIndex);
	}

	mGunshotSound = new SoundEffect();
	mGunshotSound->LoadClip("Gunshot.wav");

	mScreamSound = new SoundEffect();
	mScreamSound->LoadClip("Scream.wav");

	SetScale(Vector3D(10, 10, 10));
	SetRotation(Vector3D(270, 0, 0));

	sphere = new Sphere(mTransform.position, 1.7f, this);
	components.push_back(sphere);
}

Level2Player::~Level2Player()
{
	SDL_GameControllerClose(mController);
	mController = NULL;
}

void Level2Player::Render()
{	
	glPushMatrix();
	glTranslatef(fireEnd.x, fireEnd.y, fireEnd.z);
	glutSolidSphere(0.5, 5, 5);
	glPopMatrix();

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

void Level2Player::Update(float deltaTime, SDL_Event e)
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

		case SDLK_1:
			ChangeWeapon(1);
			break;

		case SDLK_2:
			ChangeWeapon(2);
			break;

		case SDLK_3:
			ChangeWeapon(3);
			break;

		case SDLK_4:
			ChangeWeapon(4);
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
	}
	
	//=====
	//Gamepad Controls
	if (mController != NULL)
	{
		stickInput = Vector2D(
			SDL_GameControllerGetAxis(mController, SDL_GameControllerAxis(SDL_CONTROLLER_AXIS_LEFTX)),
			SDL_GameControllerGetAxis(mController, SDL_GameControllerAxis(SDL_CONTROLLER_AXIS_LEFTY)));

		//Is the magnitude more than the circular deadzone area?
		if (stickInput.Magnitude() > pow(JOYSTICK_DEAD_ZONE, 2))
		{
			//Input amounts are set between -1 and 1
			xDir = stickInput.x / JOYSTICK_MAX_AXIS;
			yDir = stickInput.y / JOYSTICK_MAX_AXIS;
		}
		else
		{
			//If the stick is inside the deadzone then set the input amounts to 0
			xDir = 0;
			yDir = 0;
		}

		//Get Stick Angle
		lookInput = Vector2D(
			SDL_GameControllerGetAxis(mController, SDL_GameControllerAxis(SDL_CONTROLLER_AXIS_RIGHTX)),
			SDL_GameControllerGetAxis(mController, SDL_GameControllerAxis(SDL_CONTROLLER_AXIS_RIGHTY))
		);

		if (lookInput.Magnitude() > pow(JOYSTICK_DEAD_ZONE, 2))
		{
			xLook = lookInput.x / JOYSTICK_MAX_AXIS;
			yLook = lookInput.y / JOYSTICK_MAX_AXIS;

			lookAngle = (atan2(-yLook, xLook) * (180 / M_PI)) + 90;
			fireEnd = mTransform.position + Vector3D(xLook, 0, yLook).Normalise() * weaponRange;
			FireWeapon(deltaTime);
		}
		else
		{
			xLook = 0;
			yLook = 0;
		}

		//Change Weapon Types
		if (SDL_GameControllerGetButton(mController, SDL_GameControllerButton(SDL_CONTROLLER_BUTTON_A)))
		{
			ChangeWeapon(1);
		}
		if (SDL_GameControllerGetButton(mController, SDL_GameControllerButton(SDL_CONTROLLER_BUTTON_B)))
		{
			ChangeWeapon(2);
		}
		if (SDL_GameControllerGetButton(mController, SDL_GameControllerButton(SDL_CONTROLLER_BUTTON_X)))
		{
			ChangeWeapon(3);
		}
		if (SDL_GameControllerGetButton(mController, SDL_GameControllerButton(SDL_CONTROLLER_BUTTON_Y)))
		{
			ChangeWeapon(4);
		}
	}
	//=====



	//Add position using input modifier
	SetPosition(Vector3D(GetPosition().x + ((xDir * movement) * deltaTime), GetPosition().y, GetPosition().z + ((yDir * movement) * deltaTime)));

	//Set rotation based on input direction
	SetRotation(Vector3D(GetRotation().x, lookAngle, GetRotation().z));

	sphere->SetCollided(false, NULL);
	sphere->Update(mTransform.position);
}

void Level2Player::FireWeapon(float deltaTime)
{
	if (fireReady)
	{
		for (int i = 0; i < mManager->GetEnemies().size(); i++)
		{
			if (Collision::BoxLineCollision(mManager->GetEnemies()[i]->GetBoundingBox(), mTransform.position, fireEnd))
			{
				mManager->GetEnemies()[i]->Hit(activeWeapon, 15, this);
			}
		}
		fireReady = false;
		mGunshotSound->Play();
	}
	else
	{
		fireTimer -= deltaTime;
		if (fireTimer <= 0)
		{
			fireReady = true;
			fireTimer = 0.2f;
		}
	}
}

void Level2Player::ChangeWeapon(int type)
{
	if (activeWeapon != type)
	{
		activeWeapon = type;
		cout << activeWeapon << endl;
	}
}

void Level2Player::Hit()
{
	//Kill player
	mScreamSound->Play();

	cout << "Player Hit" << endl;
	mManager->PlayerKilled(this);
}