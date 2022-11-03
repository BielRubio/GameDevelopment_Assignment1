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
	//Initial fade in and textures drawing
	if (fadeIn == true) {
		if (fading >= 1) { fading--; };
	}
	app->render->DrawTexture(MENUD, x, 0);
	if (Play == true && fontFading <= 230) {
		app->font->BlitText(80, 60, WF, "play");
		app->font->BlitText(80, 100, GF, "exit");
	}
	if (Play == false && fontFading <= 230) {
		app->font->BlitText(80, 60, GF, "play");
		app->font->BlitText(80, 100, WF, "exit");
	}
	if (PlaySelected == true) {
		if (fontFading <= 254) { fontFading+=4; };
	}
	app->render->DrawRectangle({ 0,0,1100,800 }, 0, 0, 0, fading);
	if (fontFading <= 254) {
		app->render->DrawRectangle({ -20,90,80,80 }, 0, 0, 0, fontFading);
	}
	// Menu animation
	if (fontFading >= 255) {
		x -= 2;
		if (x <= -300) {
			fadeIn = false;
		}
		//counter++;
		//if (counter >= 2) {
		//	counter = 0;
		//	x -= 4;
		//	if (x <= -300) {
		//		fadeIn = false;
		//	}
		//}
	}
	//Fade out and exit
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (Play == true) {
			app->audio->PlayFx(select);
			PlaySelected = true;
			//fadeIn = false;
		}
		if (Play == false) {
			ret = false;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
		if (Play == false) {
			app->audio->PlayFx(change);
		}
		Play = true;
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		if (Play == true) {
			app->audio->PlayFx(change);
		}
		Play = false;
	}
	if (fadeIn == false ) {
		//app->entityManager->active = true;
		//app->physics->active = true;
		app->scene->CanPlayerMove = true;
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
	LOG("Freeing menu");

	return true;
}
