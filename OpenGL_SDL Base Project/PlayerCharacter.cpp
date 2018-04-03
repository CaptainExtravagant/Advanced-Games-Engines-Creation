#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Vector3D startPosition, string modelFileName, string textureFileName) : GameObject(startPosition, modelFileName, textureFileName)
{
	movement = 4.0f;
	hits = 0;
	//SetScale(Vector3D(0.1f, 0.1f, 0.1f));

	sphere = new Sphere(mTransform.position, 1.7f, this);

	components.push_back(sphere);
}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			//Move Right
			SetPosition(Vector3D(GetPosition().x + (movement * deltaTime), GetPosition().y, GetPosition().z));

			//SetRotation(Vector3D(GetRotation().x, GetRotation().y, GetRotation().z - (movement)));
			break;

		case SDLK_a:
			//Move Left
			SetPosition(Vector3D(GetPosition().x - (movement * deltaTime), GetPosition().y, GetPosition().z));

			//SetRotation(Vector3D(GetRotation().x, GetRotation().y, GetRotation().z + (movement)));
			break;

		case SDLK_w:
			//Move Up
			SetPosition(Vector3D(GetPosition().x, GetPosition().y, GetPosition().z - (movement * deltaTime)));

			//SetRotation(Vector3D(GetRotation().x - (movement), GetRotation().y, GetRotation().z));
			break;

		case SDLK_s:
			//Move Down
			SetPosition(Vector3D(GetPosition().x, GetPosition().y, GetPosition().z + (movement * deltaTime)));

			//SetRotation(Vector3D(GetRotation().x + (movement), GetRotation().y, GetRotation().z));
			break;
		}
	}
	sphere->SetCollided(false, NULL);
	sphere->Update(mTransform.position);
}

void PlayerCharacter::HitBall()
{
	hits += 1;
}