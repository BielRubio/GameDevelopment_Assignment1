#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

public:

private:

	SDL_Texture* texture;
	const char* texturePath;

	int width;
	int height;

	PhysBody* pbody;
	//Player state
	bool right = true, running = false;
	Animation* PlayerAnim;

};

#endif // __PLAYER_H__