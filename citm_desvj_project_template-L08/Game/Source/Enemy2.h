#ifndef __ENEMY2_H__
#define __ENEMY2_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

class Enemy2 : public Entity
{
public:

	Enemy2();
	
	virtual ~Enemy2();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	bool IsAlive(); 

	bool LoadState(pugi::xml_node& data);

	bool SaveState(pugi::xml_node& data);

	void DetectPlayer();

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
};

#endif // __ENEMY2_H__