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

	pbody = app->physics->CreateRectangle(position.x + width/2, position.y + height/2, width, height, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true);
	//Animations
	PlayerRight2.PushBack({ 2,0,12,10 });
	PlayerRight2.loop = false;
	PlayerRight2.speed = 0.2f;
	PlayerRight = &PlayerRight2;

	PlayerLeft2.PushBack({ 2,10,12,10 });
	PlayerLeft2.loop = false;
	PlayerLeft2.speed = 0.2f;
	PlayerLeft = &PlayerLeft2;

	PlayerRightRunning2.PushBack({ 2,20,13,10 });
	PlayerRightRunning2.PushBack({ 18,20,13,10 });
	PlayerRightRunning2.PushBack({ 34,20,13,10 });
	PlayerRightRunning2.loop = true;
	PlayerRightRunning2.speed = 0.12f;
	PlayerRightRunning = &PlayerRightRunning2;

	PlayerLeftRunning2.PushBack({ 1,30,13,10 });
	PlayerLeftRunning2.PushBack({ 17,30,13,10 });
	PlayerLeftRunning2.PushBack({ 33,30,13,10 });
	PlayerLeftRunning2.loop = true;
	PlayerLeftRunning2.speed = 0.12f;
	PlayerLeftRunning = &PlayerLeftRunning2;

	return true;
}

bool Player::Update()
{

	// L07 DONE 5: Add physics to the player - updated player position using physics

	float speed = 3; 
	b2Vec2 vel = b2Vec2(0, pbody->body->GetLinearVelocity().y); 
	running = false;

	//L02: DONE 4: modify the position of the player using arrow keys and render the texture
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		//
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		//
	}
		
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		vel = b2Vec2(-speed, pbody->body->GetLinearVelocity().y);
		right = false;
		running = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		vel = b2Vec2(speed, pbody->body->GetLinearVelocity().y);
		right = true;
		running = true;
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		pbody->body->ApplyForce(b2Vec2(0,-50), pbody->body->GetPosition(),true);
	}

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width/2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height/2);

	//Player Animations

	if (right == true && running == false) {
		SDL_Rect rect = PlayerRight->GetCurrentFrame();
		app->render->DrawTexture(texture, position.x, position.y,&rect);
	}
	if (right == false && running == false) {
		SDL_Rect rect = PlayerLeft->GetCurrentFrame();
		app->render->DrawTexture(texture, position.x, position.y, &rect);
	}
	if (right == true && running == true) {
		SDL_Rect rect = PlayerRightRunning->GetCurrentFrame();
		app->render->DrawTexture(texture, position.x, position.y, &rect);
		PlayerRightRunning->Update();
	}
	if (right == false && running == true) {
		SDL_Rect rect = PlayerLeftRunning->GetCurrentFrame();
		app->render->DrawTexture(texture, position.x, position.y, &rect);
		PlayerLeftRunning->Update();
	}

	return true;
}

bool Player::CleanUp()
{

	return true;
}