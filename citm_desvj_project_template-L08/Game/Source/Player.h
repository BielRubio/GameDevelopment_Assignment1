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

	void OnCollision(PhysBody* physA, PhysBody* physB);

	bool IsAlive(); 



public:

private:

	SDL_Texture* texture;
	const char* texturePath;

	//Fx
	int Step1, Step2, Jump1, aux = -1;

	int width;
	int height;
	int jumpCounter; 

	bool alive; 

	PhysBody* pbody;

	DIRECTION facing = DIRECTION::RIGHT;

	Animation* currentAnim = nullptr;

	Animation playerIdleR;
	Animation playerIdleL;
	Animation playerRunR;
	Animation playerRunL;
	Animation playerJumpR;
	Animation playerJumpL;
	Animation playerDie;

};

#endif // __PLAYER_H__