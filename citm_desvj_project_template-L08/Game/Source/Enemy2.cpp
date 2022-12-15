#include "Enemy2.h"
#include "Player.h"
#include "EntityManager.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Map.h"
#include "Point.h"
#include "Physics.h"
#include "Window.h"

Enemy2::Enemy2() : Entity(EntityType::ENEMY2)
{
	name.Create("Enemy2");

}

Enemy2::~Enemy2() {

}

bool Enemy2::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	width = parameters.attribute("width").as_int();
	height = parameters.attribute("height").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Enemy2::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	pbody = app->physics->CreateRectangle(position.x + width/2, position.y + height/2, width-10, height-8, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;
	pbody->body->SetGravityScale(0);

	//Animations
	enemyIdleR.PushBack({ 0 * width,0 * height,width,height });
	enemyIdleL.PushBack({ 0 * width,1 * height,width,height });

	enemyDropR.PushBack({ 0 * width,4 * height,width,height });
	enemyDropL.PushBack({ 0 * width,5 * height,width,height });

	for (int i = 0; i < 3; i++) {
		enemyRunR.PushBack({ i * width,2 * height,width,height });
	}
	enemyRunR.loop = true;
	enemyRunR.speed = 0.3f;

	for (int i = 0; i < 3; i++) {
		enemyRunL.PushBack({ i * width,3 * height,width,height });
	}
	enemyRunL.loop = true;
	enemyRunL.speed = 0.3f;

	for (int i = 0; i < 4; i++) {
		enemyDie.PushBack({ i * width,6 * height,width,height });
	}
	enemyDie.loop = false;
	enemyDie.speed = 0.3f;

	currentAnim = &enemyIdleR;

	return true;
}



bool Enemy2::Update()
{

	if (pbody->body->GetLinearVelocity().x > 0)
		currentAnim = &enemyIdleR;

	if (pbody->body->GetLinearVelocity().x < 0)
		currentAnim = &enemyIdleL;

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	currentAnim->Update();

	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width / 2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height / 2);

	app->render->DrawTexture(texture, position.x, position.y, &rect);
	if (app->map->DrawPathing == true) {
		app->render->DrawCircle(position.x * app->win->GetScale(), position.y * app->win->GetScale(), 16 * 10 * app->win->GetScale(), 255, 255, 0, 100);
	}
	//app->render->DrawRectangle({position.x, position.y, width, height}, 255, 0,0);
	app->scene->origin = app->map->WorldToMap(position.x+4, position.y+4);
	app->scene->origin = app->map->MapToWorld(app->scene->origin.x, app->scene->origin.y);
	return true;
}

bool Enemy2::CleanUp()
{
	return true;
}

void Enemy2::OnCollision(PhysBody* physA, PhysBody* physB) {

}

bool Enemy2::IsAlive() {
	return alive; 
}

bool Enemy2::LoadState(pugi::xml_node& data) {

	/*position.x = data.child("enemy_stats").attribute("position_x").as_int();
	position.y = data.child("enemy_stats").attribute("position_y").as_int();
	pbody->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0);*/

	return true;
}

bool Enemy2::SaveState(pugi::xml_node& data) {

	/*pugi::xml_node enemy_stats = data.append_child("enemy_stats");
	data.child("enemy_stats").append_attribute("position_x") = position.x;
	data.child("enemy_stats").append_attribute("position_y") = position.y;*/

	return true; 
}

void Enemy2::DetectPlayer() {

}

void Enemy2::Patrol() {

}