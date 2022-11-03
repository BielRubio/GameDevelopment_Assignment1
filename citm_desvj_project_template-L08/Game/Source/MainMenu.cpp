#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Menu.h"
#include "MainMenu.h"
#include "Entitymanager.h"
#include "Scene.h"
#include "Physics.h"
#include "ModuleFonts.h"

#include "Defs.h"
#include "Log.h"

MainMenu::MainMenu() : Module()
{
	name.Create("main menu");
}

// Destructor
MainMenu::~MainMenu()
{}

// Called before render is available
bool MainMenu::Awake(pugi::xml_node& config)
{
	LOG("Loading main menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool MainMenu::Start()
{
	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz0123456789" };
	WF = app->font->Load("Assets/Fonts/FontWhiteDef.png", lookupTable, 1);
	GF = app->font->Load("Assets/Fonts/FontGreyDef.png", lookupTable, 1);
	change = app->audio->LoadFx("Assets/Sounds/ChangeSelection.wav");
	select = app->audio->LoadFx("Assets/Sounds/Select.wav");

	return true;
}

// Called each loop iteration
bool MainMenu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool MainMenu::Update(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
		if (option == SELECTED::OPTIONS) {
			option = SELECTED::PLAY;
			app->audio->PlayFx(change);
		}
		if (option == SELECTED::EXIT) {
			option = SELECTED::OPTIONS;
			app->audio->PlayFx(change);
		}
		if (option == SELECTED::BACK) {
			option = SELECTED::MUSIC;
			app->audio->PlayFx(change);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		if (option == SELECTED::OPTIONS) {
			option = SELECTED::EXIT;
			app->audio->PlayFx(change);
		}
		if (option == SELECTED::PLAY) {
			option = SELECTED::OPTIONS;
			app->audio->PlayFx(change);
		}
		if (option == SELECTED::MUSIC) {
			option = SELECTED::BACK;
			app->audio->PlayFx(change);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (option == SELECTED::PLAY && fadeOut == false) {
			app->audio->PlayFx(select);
			fadeOut = true;
		}
		if (option == SELECTED::OPTIONS) {
			app->audio->PlayFx(select);
			option = SELECTED::MUSIC;
			options = true;
		}
		if (option == SELECTED::BACK) {
			app->audio->PlayFx(select);
			option = SELECTED::OPTIONS;
			options = false;
		}
		if (option == SELECTED::EXIT) {
			ret = false;
		}

	}
	if (fadeIn == true) {
		if (fading >= 1) { fading--; };
		if (fading == 0) { fadeIn = false; };
	}
	if (fadeOut == true) {
		if (fading2 <= 254) { fading2++; };
	}
	if (fading2 == 255) {
		app->scene->active = true;
		app->menu->active = true;
		app->entityManager->active = true;
		app->physics->active = true;
		app->mainmenu->active = false;
	}
	if (option == SELECTED::PLAY && options == false) {
		app->font->BlitText(145, 40, WF, "play");
		app->font->BlitText(137, 80, GF, "options");
		app->font->BlitText(145, 120, GF, "exit");
	}
	if (option == SELECTED::OPTIONS && options == false) {
		app->font->BlitText(145, 40, GF, "play");
		app->font->BlitText(137, 80, WF, "options");
		app->font->BlitText(145, 120, GF, "exit");
	}
	if (option == SELECTED::EXIT && options == false) {
		app->font->BlitText(145, 40, GF, "play");
		app->font->BlitText(137, 80, GF, "options");
		app->font->BlitText(145, 120, WF, "exit");
	}
	if (option == SELECTED::MUSIC && options == true) {
		app->font->BlitText(142, 60, WF, "music");
		app->font->BlitText(145, 100, GF, "back");
	}
	if (option == SELECTED::BACK && options == true) {
		app->font->BlitText(142, 60, GF, "music");
		app->font->BlitText(145, 100, WF, "back");
	}
	app->render->DrawRectangle({ 0,0,1100,800 }, 0, 0, 0, fading);
	app->render->DrawRectangle({ 0,0,1100,800 }, 0, 0, 0, fading2);

	return ret;
}

// Called each loop iteration
bool MainMenu::PostUpdate()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool MainMenu::CleanUp()
{
	LOG("Freeing main menu");

	return true;
}
