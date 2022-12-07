#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "MainMenu.h"
#include "Intro.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	// iterate all objects in the scene
	// Check https://pugixml.org/docs/quickstart.html#access

	/*for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;
	}*/

	for (pugi::xml_node sawNode = config.child("saw"); sawNode; sawNode = sawNode.next_sibling("saw"))
	{
		Saw* saw = (Saw*)app->entityManager->CreateEntity(EntityType::SAW);
		saw->parameters = sawNode;
	}

	//L02: DONE 3: Instantiate the player using the entity manager
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->parameters = config.child("player");

	Item* trophy =(Item*)app->entityManager->CreateEntity(EntityType::ITEM);
	trophy->parameters = config.child("trophy");

	Enemy* ene = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	ene->parameters = config.child("enemy");

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	//img = app->tex->Load("Assets/Textures/test.png");
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");
	
	// L03: DONE: Load map
	app->map->Load();
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	// L04: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width,
		app->map->mapData.height,
		app->map->mapData.tileWidth,
		app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());

	app->win->SetTitle(title.GetString());

	//Initialize trophy texture
	//trophyTex = app->tex->Load("Assets/Textures/trophy.png");
	BGtexture = app->tex->Load("Assets/Maps/parallax1.png");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (Music == false) {
		app->audio->PlayMusic("Assets/Sounds/candybattleLONG.wav");
		Music = true;
	}
	// L03: DONE 3: Request App to Load / Save when pressing the keys F5 (save) / F6 (load)
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		if (app->physics->debug == true) {
			app->physics->debug = false;
		}
		else if (app->physics->debug == false) {
			app->physics->debug = true;
		}
	}
	
	//Camera on player
	/*app->render->camera.x = -1 * (player->position.x * app->win->GetScale() - app->render->camera.w / 2);
	app->render->camera.y = -1 * (player->position.y * app->win->GetScale() - app->render->camera.h / 2);*/

	// Draw map
	app->map->Draw();

	//app->render->DrawTexture(MapAdjustment, -100, 75);
	app->render->DrawRectangle({ 0,0,-150,560 }, 34, 32, 52);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(trophyTex);
	app->tex->UnLoad(BGtexture);
	return true;
}

bool Scene::LoadState(pugi::xml_node& data) {
	return true; 
}

bool Scene::SaveState(pugi::xml_node& data) {
	return true; 
}
