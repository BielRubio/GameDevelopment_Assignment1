#include "Saw.h"
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

Saw::Saw() : Entity(EntityType::SAW)
{
	name.Create("saw");
}

Saw::~Saw() {}

bool Saw::Awake() {

	position.x = parameters.attribute("x1").as_int();
	position.y = parameters.attribute("y1").as_int();
	p1.x = parameters.attribute("x1").as_int();
	p1.y = parameters.attribute("y1").as_int();
	p2.x = parameters.attribute("x2").as_int();
	p2.y = parameters.attribute("y2").as_int();
	noMove = parameters.attribute("static").as_bool();
	speed = parameters.attribute("speed").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Saw::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	pbody = app->physics->CreateCircle(position.x +12, position.y + 12, 12, bodyType::STATIC);
	//pbody = app->physics->CreateRectangle(position.x + 12, position.y + 12, 18,18, bodyType::STATIC);
	pbody->body->SetFixedRotation(true);

	pbody->ctype = ColliderType::SPIKES; 

	//Animation

	spinAnim.PushBack({ 0,0,24,24 });
	spinAnim.PushBack({ 24,0,24,24 });
	spinAnim.speed = 0.3f;
	spinAnim.loop = true;

	currentAnimation = &spinAnim;

	return true;
}

bool Saw::Update()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	currentAnimation->Update();

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 12;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 12;

	app->render->DrawTexture(texture, position.x, position.y, &rect);

	return true;
}

bool Saw::CleanUp()
{
	return true;
}