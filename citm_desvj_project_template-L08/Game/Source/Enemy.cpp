#include "Enemy.h"
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
#include "Pathfinding.h"
#include "DynArray.h"

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

	tileX = app->tex->Load("Assets/Maps/path_square.png");

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

	vel = b2Vec2(0, 0);

	return true;
}



bool Enemy::Update()
{
	float speed = 2; 
	position.x = METERS_TO_PIXELS((pbody->body->GetTransform().p.x) - width / 2);
	position.y = METERS_TO_PIXELS((pbody->body->GetTransform().p.y) - height / 2);

	if (pbody->body->GetLinearVelocity().x > 0)
		currentAnim = &enemyRunR;

	if (pbody->body->GetLinearVelocity().x < 0)
		currentAnim = &enemyRunL;

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	currentAnim->Update();

	app->render->DrawTexture(texture, position.x, position.y, &rect);
	if (app->map->DrawPathing == true) {
		app->render->DrawCircle(position.x * app->win->GetScale(), position.y * app->win->GetScale(), 16 * 10 * app->win->GetScale(), 255, 255, 0, 100);
	}

	iPoint playerPos = app->map->WorldToMap(METERS_TO_PIXELS(app->scene->player->pbody->body->GetPosition().x), METERS_TO_PIXELS(app->scene->player->pbody->body->GetPosition().y));
	iPoint enemyPos = app->map->WorldToMap(METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - width / 2, METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - height / 2);


	app->pathfinding->CreatePath(enemyPos, playerPos);
	
	enemyPath.Clear(); 
	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();
 
	for (uint i = 0; i < path->Count(); i++){
		enemyPath.PushBack(iPoint(path->At(i)->x, path->At(i)->y));
	}

	//Draw the path
	for (uint i = 0; i < enemyPath.Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(enemyPath.At(i)->x, enemyPath.At(i)->y);
		app->render->DrawTexture(tileX, pos.x, pos.y);
	}

	if (enemyPath.Count() > 1) {
		DetectPlayer(playerPos, enemyPos);
		if (state == EnemyState::MOVING) {
			if (enemyPath.At(1)->x - enemyPath.At(0)->x > 0) {
				if (pbody->body->GetLinearVelocity().x < 2.5) {
					pbody->body->ApplyForce(b2Vec2(1.0f, 0.0f), pbody->body->GetWorldCenter(), true);
				}
			}
			else if (enemyPath.At(1)->x - enemyPath.At(0)->x < 0) {
				if (pbody->body->GetLinearVelocity().x > -2.5) {
					pbody->body->ApplyForce(b2Vec2(-1.0f, 0.0f), pbody->body->GetWorldCenter(), true);
				}
			}
			else {
				pbody->body->ApplyForce(b2Vec2(-pbody->body->GetLinearVelocity().x * 0.1f, 0.0f), pbody->body->GetWorldCenter(), true);
			}
		}
	}

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

	position.x = data.child("enemy_stats").attribute("position_x").as_int();
	position.y = data.child("enemy_stats").attribute("position_y").as_int();
	pbody->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0);

	return true;
}

bool Enemy::SaveState(pugi::xml_node& data) {

	pugi::xml_node enemy_stats = data.append_child("enemy_stats");
	data.child("enemy_stats").append_attribute("position_x") = position.x;
	data.child("enemy_stats").append_attribute("position_y") = position.y;

	return true; 
}

void Enemy::DetectPlayer(iPoint playerPos, iPoint enemyPos) {
	if (playerPos.DistanceTo(enemyPos) <= 5) {
		state = EnemyState::MOVING; 
		LOG("MOVING FlyingEnemy");
	}
	else {
		state = EnemyState::IDLE; 
		LOG("IDLE FlyingEnemy");
	}
}

void Enemy::Patrol() {

}