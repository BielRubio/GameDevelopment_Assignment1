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
#include "ModuleFonts.h"
#include "Entity.h"
#include "DeathMenu.h"

#include "Defs.h"
#include "Log.h"

DeathMenu::DeathMenu() : Module()
{
	name.Create("menu");
}

// Destructor
DeathMenu::~DeathMenu()
{}

// Called before render is available
bool DeathMenu::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DeathMenu::Start()
{
	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz0123456789" };
	WF = app->font->Load("Assets/Fonts/FontWhiteDef.png", lookupTable, 1);
	GF = app->font->Load("Assets/Fonts/FontGreyDef.png", lookupTable, 1);
	change = app->audio->LoadFx("Assets/Sounds/ChangeSelection.wav");
	select = app->audio->LoadFx("Assets/Sounds/Select.wav");
	//MENUD = app->tex->Load("Assets/Textures/Menu_Gradient.png");
	return true;
}

// Called each loop iteration
bool DeathMenu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool DeathMenu::Update(float dt)
{
	bool ret = true;
	//Death Menu
	if (app->scene->player->DeathAnimationFinished == true) {
		app->render->DrawRectangle({ -1000,-1000,10000,2000 }, 0, 0, 0, fading);
		if (fading <= 99) {
			fading++;
		}
	}

	return ret;
}

// Called each loop iteration
bool DeathMenu::PostUpdate()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool DeathMenu::CleanUp()
{
	LOG("Freeing menu");

	return true;
}
