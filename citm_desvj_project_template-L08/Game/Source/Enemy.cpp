#include "Enemy.h"
#include "Player.h"
#include "EntityManager.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Window.h"

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");

}

Enemy::~Enemy() {

}

bool Enemy::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	width = parameters.attribute("width").as_int();
	height = parameters.attribute("height").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Enemy::Start() {

	//initilize textures
	//texture = app->tex->Load(texturePath);
	pbody = app->physics->CreateRectangle(position.x + width/2, position.y + height/2, width, height, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

	return true;
}



bool Enemy::Update()
{

	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width / 2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height / 2);

	app->render->DrawRectangle({position.x, position.y, width, height}, 255, 0,0);

	return true;
}

bool Enemy::CleanUp()
{
	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {

}

bool Enemy::IsAlive() {
	return alive; 
}

bool Enemy::LoadState(pugi::xml_node& data) {

	/*position.x = data.child("enemy_stats").attribute("position_x").as_int();
	position.y = data.child("enemy_stats").attribute("position_y").as_int();
	pbody->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0);*/

	return true;
}

bool Enemy::SaveState(pugi::xml_node& data) {

	/*pugi::xml_node enemy_stats = data.append_child("enemy_stats");
	data.child("enemy_stats").append_attribute("position_x") = position.x;
	data.child("enemy_stats").append_attribute("position_y") = position.y;*/

	return true; 
}