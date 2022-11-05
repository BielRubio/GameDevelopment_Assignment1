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
	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz0123456789" };
	WF = app->font->Load("Assets/Fonts/FontWhiteDef.png", lookupTable, 1);
	GF = app->font->Load("Assets/Fonts/FontGreyDef.png", lookupTable, 1);
	change = app->audio->LoadFx("Assets/Sounds/ChangeSelection.wav");
	select = app->audio->LoadFx("Assets/Sounds/Select.wav");
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
	bool ret = true;
	//Fade out and exit
	if (fadeIn == true) {
		if (fading >= 1) { fading--; };
		if (fading == 0) { fadeIn = false; };
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

	}
	if (option == SELECTED::FIRST) {
		app->font->BlitText(140, 40, WF, "empty");
		app->font->BlitText(140, 60, GF, "empty");
		app->font->BlitText(140, 80, GF, "empty");
		}
	if (option == SELECTED::SECOND) {
		app->font->BlitText(140, 40, GF, "empty");
		app->font->BlitText(140, 60, WF, "empty");
		app->font->BlitText(140, 80, GF, "empty");
	}
	if (option == SELECTED::THIRD) {
		app->font->BlitText(140, 40, GF, "empty");
		app->font->BlitText(140, 60, GF, "empty");
		app->font->BlitText(140, 80, WF, "empty");
	}
	app->render->DrawRectangle({ app->scene->player->positionX,  app->scene->player->positionX,1100,800 }, 0, 0, 0, fading);
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
	LOG("Freeing menu");

	return true;
}
