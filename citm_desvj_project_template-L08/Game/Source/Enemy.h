#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

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

public:

	int positionX, positionY;

	PhysBody* pbody;

	bool alive, invincible = false;
	
private:

	SDL_Texture* texture;
	const char* texturePath;

	int width;
	int height;
};

#endif // __ENEMY_H__