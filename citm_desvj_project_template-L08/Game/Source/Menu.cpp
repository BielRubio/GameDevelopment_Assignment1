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
	//Initial fade in
	if (fadeIn == true) {
		if (fading >= 1) { fading--; };
	}
	//if (fadeIn == false) {
	//	if (fading <= 254) { fading++; };
	//}
	app->render->DrawTexture(MENUD, -120, 0);
	app->render->DrawRectangle({ 0,0,1100,800 }, 0, 0, 0, fading);
	//Fade out
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && fading == 0) {
		fadeIn = false;
	}
	if (fadeIn == false ) {
		app->entityManager->active = true;
		app->physics->active = true;
		app->menu->active = false;
	}

	return true;
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
