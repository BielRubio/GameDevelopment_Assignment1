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
	texture = app->tex->Load(texturePath);
	pbody = app->physics->CreateRectangle(position.x + width/2, position.y + height/2, width-4, height-4, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

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



bool Enemy::Update()
{

	if (pbody->body->GetLinearVelocity().x > 0)
		currentAnim = &enemyRunR;

	if (pbody->body->GetLinearVelocity().x < 0)
		currentAnim = &enemyRunL;

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	currentAnim->Update();

	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width / 2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height / 2);

	app->render->DrawTexture(texture, position.x, position.y, &rect);
	//app->render->DrawRectangle({position.x, position.y, width, height}, 255, 0,0);

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