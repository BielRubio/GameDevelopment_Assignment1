#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Path.h"
#include "Physics.h"
#include "DynArray.h"
struct SDL_Texture;

enum class EnemyState {
	IDLE, 
	MOVING
};

class Enemy : public Entity
{
public:

	Enemy();
	
	virtual ~Enemy();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	bool IsAlive(); 

	bool LoadState(pugi::xml_node& data);

	bool SaveState(pugi::xml_node& data);

	void DetectPlayer(iPoint playerPos, iPoint enemyPos);

	void Patrol();

public:

	PhysBody* pbody;

	bool alive, invincible = false;
	
private:

	SDL_Texture* texture;
	const char* texturePath;

	Animation* currentAnim = nullptr;

	Animation enemyIdleR;
	Animation enemyIdleL;
	Animation enemyRunR;
	Animation enemyRunL;
	Animation enemyDropR;
	Animation enemyDropL;
	Animation enemyDie;

	int width;
	int height;

	EnemyState state; 

	b2Vec2 vel;
	DynArray<iPoint> enemyPath; 
};

#endif // __ENEMY_H__