#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Intro.h"
#include "Menu.h"

#include "Defs.h"
#include "Log.h"

Intro::Intro() : Module()
{
	name.Create("intro");
}

// Destructor
Intro::~Intro()
{}

// Called before render is available
bool Intro::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Intro::Start()
{
	INTROD = app->tex->Load("Assets/Textures/Intro.png");
	return true;
}

// Called each loop iteration
bool Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Intro::Update(float dt)
{
	//Initial fade in
	if (fadeIn == true) {
		if (fading >= 1) { fading--; };
	}
	if (fadeIn == false) {
		if (fading <= 254) { fading++; };
	}
	app->render->DrawTexture(INTROD, 400, 300);
	app->render->DrawRectangle({ 0,0,1100,800 }, 0, 0, 0, fading);
	counter++;
	//Fade out
	if (counter >= 400) {
		fadeIn = false;
	}
	//Scene transition to menu
	if (fadeIn == false && fading == 255 && counter > 750) {
		app->menu->active = true;
		app->intro->active = false;
	}

	return true;
}

// Called each loop iteration
bool Intro::PostUpdate()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool Intro::CleanUp()
{
	LOG("Freeing intro");

	return true;
}
