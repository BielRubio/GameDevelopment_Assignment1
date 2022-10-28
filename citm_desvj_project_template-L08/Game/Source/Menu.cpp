#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Menu.h"
#include "Entitymanager.h"
#include "Scene.h"
#include "Physics.h"

#include "Defs.h"
#include "Log.h"

Menu::Menu() : Module()
{
	name.Create("menu");
}

// Destructor
Menu::~Menu()
{}

// Called before render is available
bool Menu::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Menu::Start()
{
	MENUD = app->tex->Load("Assets/Textures/Menu_Gradient.png");
	PLAYW = app->tex->Load("Assets/Textures/PlayWS.png");
	PLAYG = app->tex->Load("Assets/Textures/PlayGS.png");
	EXITW = app->tex->Load("Assets/Textures/ExitWS.png");
	EXITG = app->tex->Load("Assets/Textures/ExitGS.png");
	return true;
}

// Called each loop iteration
bool Menu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Menu::Update(float dt)
{
	bool ret = true;
	//Initial fade in and textures drawing
	if (fadeIn == true) {
		if (fading >= 1) { fading--; };
	}
	app->render->DrawTexture(MENUD, -120, 0);
	if (Play == true) {
		app->render->DrawTexture(PLAYW, 2, 80);
		app->render->DrawTexture(EXITG, 0, 110);
	}
	if (Play == false) {
		app->render->DrawTexture(PLAYG, 2, 80);
		app->render->DrawTexture(EXITW, 0, 110);
	}
	app->render->DrawRectangle({ 0,0,1100,800 }, 0, 0, 0, fading);
	//Fade out and exit
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (Play == true) {
			fadeIn = false;
		}
		if (Play == false) {
			ret = false;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
		Play = true;
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		Play = false;
	}
	if (fadeIn == false ) {
		app->entityManager->active = true;
		app->physics->active = true;
		app->menu->active = false;
	}

	return ret;
}

// Called each loop iteration
bool Menu::PostUpdate()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool Menu::CleanUp()
{
	LOG("Freeing intro");

	return true;
}
