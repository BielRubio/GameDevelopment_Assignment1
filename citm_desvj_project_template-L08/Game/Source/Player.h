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

	enum class DIRECTION {
		RIGHT = 1,
		LEFT
	};

	DIRECTION facing = DIRECTION::RIGHT;

	Animation* currentAnim = nullptr;

	Animation playerIdleR;
	Animation playerIdleL;
	Animation playerRunR;
	Animation playerRunL;
	
};

#endif // __PLAYER_H__