#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

enum class State {
	LANDED,
	JUMPING,
	COLLIDING,
	MOVING_RIGHT,
	MOVING_LEFT
};

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

	bool LoadState(pugi::xml_node& data);

	bool SaveState(pugi::xml_node& data);

public:

	bool DeathAnimationFinished = false;

	PhysBody* pbody;

	bool alive, invincible = false;
	
private:

	SDL_Texture* texture;
	const char* texturePath;

	//Fx
	int Step1, Step2, StepMetalic1, StepMetalic2, Jump1, DeathSound, aux = -1;

	int width;
	int height;
	int jumpCounter; 
	int MaxJumps = 2;

	State playerState; 


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