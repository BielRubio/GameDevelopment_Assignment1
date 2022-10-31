#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"


class Menu : public Module
{
public:

	Menu();

	// Destructor
	virtual ~Menu();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

private:
	//int counter = 0;
	int fading = 255, fontFading = 0, change, select, x = -120;
	bool fadeIn = true, Play = true, PlaySelected = false;
	SDL_Texture* MENUD;
	SDL_Texture* PLAYW;
	SDL_Texture* PLAYG;
	SDL_Texture* EXITW;
	SDL_Texture* EXITG;
};

#endif // __MENU_H__

