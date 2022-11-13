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
#include "DeathMenu.h"

#include "Defs.h"
#include "Log.h"

MainMenu::MainMenu() : Module()
{
	name.Create("mainmenu");
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
	BG = app->tex->Load("Assets/Textures/TitleScreen_BG.png");

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

	app->render->DrawTexture(BG,0,0);
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (app->deathmenu->finished == true) {
		fading = 255;
		fading2 = 0;
		fadeIn = true;
		fadeOut = false;
		options = false;
		app->deathmenu->finished = false;
	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		if (option == SELECTED::OPTIONS) {
			option = SELECTED::PLAY;
			app->audio->PlayFxWithVolume(change,0,70);
		}
		if (option == SELECTED::EXIT) {
			option = SELECTED::OPTIONS;
			app->audio->PlayFxWithVolume(change, 0, 70);
		}
		if (option == SELECTED::BACK) {
			option = SELECTED::MUSIC;
			app->audio->PlayFxWithVolume(change, 0, 70);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
		if (option == SELECTED::OPTIONS) {
			option = SELECTED::EXIT;
			app->audio->PlayFxWithVolume(change, 0, 70);
		}
		if (option == SELECTED::PLAY) {
			option = SELECTED::OPTIONS;
			app->audio->PlayFxWithVolume(change, 0, 70);
		}
		if (option == SELECTED::MUSIC) {
			option = SELECTED::BACK;
			app->audio->PlayFxWithVolume(change, 0, 70);
		}
	}
	if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) && options == true) {
		if (app->audio->volume >= 1) {
			app->audio->volume--;
			app->audio->PlayFxWithVolume(change, 0, 70);
		}
	}
	if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) && options == true) {
		if (app->audio->volume <= 63) {
			app->audio->volume++;
			app->audio->PlayFxWithVolume(change, 0, 70);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (option == SELECTED::PLAY && fadeOut == false && fadeIn == false) {
			app->audio->PlayFxWithVolume(select, 0, 70);
			fadeOut = true;
		}
		if (option == SELECTED::OPTIONS) {
			app->audio->PlayFxWithVolume(select, 0, 70);
			option = SELECTED::MUSIC;
			options = true;
		}
		if (option == SELECTED::BACK) {
			app->audio->PlayFxWithVolume(select, 0, 70);
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
		app->scene->player->active = true;
		app->entityManager->active = true;
		app->physics->active = true;
		app->scene->CanPlayerMove = true;
		//app->menu->active = true;
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
		app->render->DrawRectangle({ 125,80,64,10 }, 20, 20, 20);
		app->render->DrawRectangle({ 125,80,app->audio->volume,10 }, 255, 255, 255);
	}
	if (option == SELECTED::BACK && options == true) {
		app->font->BlitText(142, 60, GF, "music");
		app->font->BlitText(145, 100, WF, "back");
		app->render->DrawRectangle({ 125,80,64,10 }, 20, 20, 20);
		app->render->DrawRectangle({ 125,80,app->audio->volume,10 }, 255, 255, 255);
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
	app->font->UnLoad(WF);
	app->font->UnLoad(GF);
	app->tex->UnLoad(BG);

	return true;
}
