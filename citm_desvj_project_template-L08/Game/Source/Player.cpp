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

	pbody = app->physics->CreateRectangle(position.x + width/2, position.y + height/2, width-4, height, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true);

	//Animations
	playerIdleR.PushBack({ 0 * width,0 * height,width,height });
	playerIdleL.PushBack({ 0 * width,1 * height,width,height });
	
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

	currentAnim = &playerIdleR;

	return true;
}

bool Player::Update()
{

	float speed = 3; 
	b2Vec2 vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && app->scene->CanPlayerMove == true) {
		vel = b2Vec2(-speed, pbody->body->GetLinearVelocity().y);
		facing = DIRECTION::LEFT;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && app->scene->CanPlayerMove == true) {
		vel = b2Vec2(speed, pbody->body->GetLinearVelocity().y);
		facing = DIRECTION::RIGHT;
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && app->scene->CanPlayerMove == true) {
		pbody->body->ApplyForce(b2Vec2(0,-50), pbody->body->GetPosition(),true);
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

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	currentAnim->Update();

	app->render->DrawTexture(texture, position.x, position.y+1, &rect);
	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width / 2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height / 2);

	return true;
}

bool Player::CleanUp()
{

	return true;
}