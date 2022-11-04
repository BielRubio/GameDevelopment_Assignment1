#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Window.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");

}

Player::~Player() {

}

bool Player::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	width = parameters.attribute("width").as_int();
	height = parameters.attribute("height").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	pbody = app->physics->CreateRectangle(position.x + width/2, position.y + height/2, width-4, height-4, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true);
	
	pbody->listener = this; 

	pbody->ctype = ColliderType::PLAYER; 

	jumpCounter = 0; 

	alive = true; 
	//Sounds
	Step1 = app->audio->LoadFx("Assets/Sounds/Player/FootGravel1.wav");
	Step2 = app->audio->LoadFx("Assets/Sounds/Player/FootGravel2.wav");
	Jump1 = app->audio->LoadFx("Assets/Sounds/Player/Jump1.wav");

	//Animations
	playerIdleR.PushBack({ 0 * width,0 * height,width,height });
	playerIdleL.PushBack({ 0 * width,1 * height,width,height });

	playerJumpR.PushBack({ 0 * width,4 * height,width,height });
	playerJumpL.PushBack({ 0 * width,5 * height,width,height });
	
	for (int i = 0; i < 3; i++) {
		playerRunR.PushBack({ i * width,2 * height,width,height });
	}
	playerRunR.loop = true;
	playerRunR.speed = 0.3f;
	
	for (int i = 0; i < 3; i++) {
		playerRunL.PushBack({ i * width,3 * height,width,height });
	}
	playerRunL.loop = true;
	playerRunL.speed = 0.3f;

	for (int i = 0; i < 4; i++) {
		playerDie.PushBack({ i * width,6 * height,width,height });
	}
	playerDie.loop = false;
	playerDie.speed = 0.3f;

	currentAnim = &playerIdleR;

	return true;
}

bool Player::Update()
{

	float speed = 3; 
	b2Vec2 vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		alive = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && app->scene->CanPlayerMove == true) {
		vel = b2Vec2(-speed, pbody->body->GetLinearVelocity().y);
		facing = DIRECTION::LEFT;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && app->scene->CanPlayerMove == true) {
		vel = b2Vec2(speed, pbody->body->GetLinearVelocity().y);
		facing = DIRECTION::RIGHT;
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && app->scene->CanPlayerMove == true && jumpCounter < 2) {
		vel = b2Vec2(pbody->body->GetLinearVelocity().x, 0);
		pbody->body->SetLinearVelocity(vel);
		pbody->body->ApplyForce(b2Vec2(0,-37), pbody->body->GetPosition(),true);
		app->audio->PlayFxWithVolume(Jump1, 0, 30);
		jumpCounter++;
	}

	//Fx
	if (vel.x != 0 && vel.y == 0) {
		aux++;
		if (aux == 0) {
			app->audio->PlayFxWithVolume(Step1,0,25);
		}
		if (aux == 10) {
			app->audio->PlayFxWithVolume(Step2,0,25);
			aux = -10;
		}
	}
	
	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	if (facing == DIRECTION::RIGHT && vel.x == 0) {
		currentAnim = &playerIdleR;
	}
	if (facing == DIRECTION::LEFT && vel.x == 0) {
		currentAnim = &playerIdleL;
	}
	if (facing == DIRECTION::RIGHT && vel.x != 0) {
		currentAnim = &playerRunR;
	}
	if (facing == DIRECTION::LEFT && vel.x != 0) {
		currentAnim = &playerRunL;
	}
	if (facing == DIRECTION::RIGHT && vel.y != 0) {
		currentAnim = &playerJumpR;
	}
	if (facing == DIRECTION::LEFT && vel.y != 0) {
		currentAnim = &playerJumpL;
	}

	//Death
	if (alive != true) {
		pbody->body->SetActive(false);
		currentAnim = &playerDie;
		if (currentAnim->HasFinished()) {
			this->Disable();
		}
	}

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	currentAnim->Update();

	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width / 2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height / 2);

	app->render->camera.x = -1 * (position.x * app->win->GetScale() - app->render->camera.w / 2);
	app->render->camera.y = -1 * (position.y * app->win->GetScale() - app->render->camera.h / 2);

	app->render->DrawTexture(texture, position.x, position.y+1, &rect);

	return true;
}

bool Player::CleanUp()
{

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::ITEM:
		LOG("Collision ITEM");

		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		jumpCounter = 0; 
		break;
	case ColliderType::SPIKES:
		LOG("Collision SPIKES");
		alive = false; 
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}

}

bool Player::IsAlive() {
	return alive; 
}