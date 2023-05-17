#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "W2_Scene.h"
#include "EntityManager.h"
#include "Map.h"
#include "PathFinding.h"
#include "GuiManager.h"
#include "Fonts.h"
#include "TeamManager.h"
#include "Defs.h"

#include "Defs.h"
#include "Log.h"

W2_Scene::W2_Scene(bool isActive) : Module(isActive)
{
	name.Create("w2_scene");
}

// Destructor
W2_Scene::~W2_Scene()
{}

// Called before render is available
bool W2_Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading W2_Scene");
	bool ret = true;

	
	mapName = config.attribute("name").as_string();
	mapFolder = config.attribute("path").as_string();
	
	app->physics->Enable();

	npc = (NpcW2*)app->entityManager->CreateEntity(EntityType::NPCW2);
	npc->parameters = config.child("npcW2");

	if (config.child("player")) {
		player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
		player->parameters = config.child("player");
		player->position.x = config.child("player").attribute("x").as_int();
		player->position.y = config.child("player").attribute("y").as_int();
	}

	for (pugi::xml_node doorNode = config.child("door"); doorNode; doorNode = doorNode.next_sibling("door")) {
		Door* door = (Door*)app->entityManager->CreateEntity(EntityType::DOOR);
		door->parameters = doorNode;

		doors.Add(door);
	}

	for (pugi::xml_node doorNode = config.child("portal"); doorNode; doorNode = doorNode.next_sibling("portal")) {
		Portal* portal = (Portal*)app->entityManager->CreateEntity(EntityType::PORTAL);
		portal->parameters = doorNode; 

		portals.Add(portal);
	}
	


	app->entityManager->Awake(config);

	CreateDialogue(); //3MB

	pugi::xml_node chestNode4 = config.child("chest4");
	chest4 = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
	chest4->parameters = chestNode4;
	chest4->position.x = chestNode4.attribute("x").as_int();
	chest4->position.y = chestNode4.attribute("y").as_int();
	chest4->width = chestNode4.attribute("width").as_int();
	chest4->height = chestNode4.attribute("height").as_int();
	chest4->chestId = chestNode4.attribute("id").as_int();
	PhysBody* chest4PB = app->physics->CreateRectangleSensor(chest4->position.x + chest4->width / 2, chest4->position.y + chest4->height / 2, chest4->width, chest4->height, bodyType::STATIC);
	chest4PB->ctype = ColliderType::CHEST4;
	PhysBody* chest4Col = app->physics->CreateRectangle(chest4->position.x + chest4->width / 2, chest4->position.y + chest4->height / 2, chest4->width, chest4->height, bodyType::STATIC);
	chest4Col->ctype = ColliderType::UNKNOWN;

	pugi::xml_node chestNode5 = config.child("chest5");
	chest5 = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
	chest5->parameters = chestNode5;
	chest5->position.x = chestNode5.attribute("x").as_int();
	chest5->position.y = chestNode5.attribute("y").as_int();
	chest5->width = chestNode5.attribute("width").as_int();
	chest5->height = chestNode5.attribute("height").as_int();
	chest5->chestId = chestNode5.attribute("id").as_int();
	PhysBody* chest5PB = app->physics->CreateRectangleSensor(chest5->position.x + chest5->width / 2, chest5->position.y + chest5->height / 2, chest5->width, chest5->height, bodyType::STATIC);
	chest5PB->ctype = ColliderType::CHEST5;
	PhysBody* chest5Col = app->physics->CreateRectangle(chest5->position.x + chest5->width / 2, chest5->position.y + chest5->height / 2, chest5->width, chest5->height, bodyType::STATIC);
	chest5Col->ctype = ColliderType::UNKNOWN;

	pugi::xml_node chestNode6 = config.child("chest6");
	chest6 = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
	chest6->parameters = chestNode6;
	chest6->position.x = chestNode6.attribute("x").as_int();
	chest6->position.y = chestNode6.attribute("y").as_int();
	chest6->width = chestNode6.attribute("width").as_int();
	chest6->height = chestNode6.attribute("height").as_int();
	chest6->chestId = chestNode6.attribute("id").as_int();
	PhysBody* chest6PB = app->physics->CreateRectangleSensor(chest6->position.x + chest6->width / 2, chest6->position.y + chest6->height / 2, chest6->width, chest6->height, bodyType::STATIC);
	chest6PB->ctype = ColliderType::CHEST6;
	PhysBody* chest6Col = app->physics->CreateRectangle(chest6->position.x + chest6->width / 2, chest6->position.y + chest6->height / 2, chest6->width, chest6->height, bodyType::STATIC);
	chest6Col->ctype = ColliderType::UNKNOWN;

	npcPopUpTexture = app->tex->Load("Assets/Characters/Characters2_popupsDialogueCut.png");
	uiSpriteTexture = app->tex->Load("Assets/UI/UI_SpriteSheet.png");
	lvlupTexture = app->tex->Load("Assets/UI/blank.png");
	questUiTexture = app->tex->Load("Assets/UI/questUI.png");
	eKeyTexture = app->tex->Load("Assets/UI/eKey.png");
	chestTexture = app->tex->Load("Assets/Maps/World_01/highRes_Assets/hr_chest_spriteSheet.png");

	currentQuestIndex = 0;

	return ret;
}

// Called before the first frame
bool W2_Scene::Start()
{
	player->walkFx = app->audio->LoadFx("Assets/Sounds/FX/fx_grass_walk.wav");
	app->entityManager->Start();

	// L03: DONE: Load map
	bool retLoad = app->map->Load(mapName, mapFolder);

	// L12 Create walkability map
	if (retLoad) {
		int w, h;
		uchar* data = NULL;

		//bool retWalkMap = app->map->CreateWalkabilityMap(w, h, &data);
		//if(retWalkMap) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

	}

	if (isNewGame)
	{
		player->ChangePosition(871, 3117);
		isNewGame = false;
	}
	else
	{
		app->LoadGameRequest();
	}

	pauseMenuActive = false;
	exitButtonBool = false;
	zorroDialogue = false;

	// Tell to UIModule which currentMenuType
	app->uiModule->currentMenuType = DISABLED;
	// Call this function only when buttons change
	app->uiModule->ChangeButtonState(app->uiModule->currentMenuType);
	
	dialogue.push_back("");

	godMode = false;
	numTimesPigsDialogueTriggered = 0;

	app->audio->PlayMusic("Assets/Sounds/Music/music_pigs_world.ogg", 0.1f);

	Quest quest1;
	quest1.completed = false;
	quest1.description = "Leave the forest and find the magic wand";
	questList.push_back(quest1);

	Quest quest2;
	quest2.completed = false;
	quest2.description = "Look for help in the village";
	questList.push_back(quest2);

	Quest quest3;
	quest3.completed = false;
	quest3.description = "Look for the Little Red Riding Hood grandma";
	questList.push_back(quest3);

	Quest quest4;
	quest4.completed = false;
	quest4.description = "Go save LRRH";
	questList.push_back(quest4);

	Quest quest5;
	quest5.completed = false;
	quest5.description = "Get through the portal";
	questList.push_back(quest5);

	chestHRect = { 4, 36, 90, 77 };
	chestVRect = { 12, 135, 71, 101 };
	chestopenHRect = { 105, 3, 88, 108 };
	chestopenVRect = { 107, 134, 74, 100 };

	return true;
}

// Called each loop iteration
bool W2_Scene::PreUpdate()
{
	return true;
}



// Called each loop iteration
bool W2_Scene::Update(float dt)
{
	//std::cout << "X: " << player->position.x << std::endl;
	//std::cout << "Y: " << player->position.y << std::endl;
	if (app->teamManager->arasiva == true) {
		app->teamManager->startstatsup = true;
		app->teamManager->arasiva = false;
	}

	Camera();

	// L03: DONE 3: Request App to Load / Save when pressing the keys F5 (save) / F6 (load)
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		app->SaveGameRequest();
	}

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();



	GodMode();

	MoveToBattleFromDialogue();


	// Check if the current quest is completed
	if (questList[currentQuestIndex].completed || app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
		// If it is, move to the next quest
		nextQuest();
	}

	// Menu appear
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		// If player is in pause, close it
		if (player->playerState == player->PlayerState::PAUSE)
		{
			player->playerState = player->playerPrevState;

			app->uiModule->currentMenuType = DISABLED;
			// Call this function only when scene is changed
			app->uiModule->ChangeButtonState(app->uiModule->currentMenuType);
		}
		// If player is NOT in pause, open it
		else
		{
			// Save previous state to go back
			player->playerPrevState = player->playerState;
			player->playerState = player->PlayerState::PAUSE;

			app->uiModule->currentMenuType = PAUSE;
			// Call this function only when scene is changed
			app->uiModule->ChangeButtonState(app->uiModule->currentMenuType);
		}
	}


	// Draw map
	app->map->Draw();


	if (chest4->isPicked)app->render->DrawTexture(app->w2_scene->chestTexture, 1447, 2666, &app->w2_scene->chestopenHRect);
	else app->render->DrawTexture(app->w2_scene->chestTexture, 1447, 2666, &app->w2_scene->chestHRect);
	if (chest5->isPicked) app->render->DrawTexture(app->w2_scene->chestTexture, 3382, 2705, &app->w2_scene->chestopenHRect);
	else app->render->DrawTexture(app->w2_scene->chestTexture, 3382, 2705, &app->w2_scene->chestHRect);
	if (chest6->isPicked) app->render->DrawTexture(app->w2_scene->chestTexture, 2101, 1910, &app->w2_scene->chestopenVRect);
	else app->render->DrawTexture(app->w2_scene->chestTexture, 2101, 1910, &app->w2_scene->chestVRect);

	return true;
}

void W2_Scene::AppearDialogue()
{
	if (player->playerState == player->PlayerState::NPC_INTERACT)
	{
		// Tell to UIModule which currentMenuType
		app->uiModule->currentMenuType = DIALOG2;
		// Call this function only when buttons change
		app->uiModule->ChangeButtonState(app->uiModule->currentMenuType);

		for (auto& e : dialogue)
		{
			std::cout << e << std::endl;
		}

	}
}

// Called each loop iteration
bool W2_Scene::PostUpdate()
{
	bool ret = true;


	if (!godMode) app->map->PostDraw(player->position.y + 40);

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;


	// When exit button click, close app
	if (exitButtonBool == true)
	{
		return false;
	}

	

	return ret;
}

bool W2_Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	LOG("Event by %d ", control->id);

	switch (control->id)
	{
		// Option 1
	case 30:
		app->w2_scene->player->buttonOption1 = true;
		break;
		// Option 2
	case 31:
		app->w2_scene->player->buttonOption2 = true;
		break;
		// Option 3
	case 32:
		app->w2_scene->player->buttonOption3 = true;
		break;
		// Option 4
	case 33:
		app->w2_scene->player->buttonOption4 = true;
	default:
		break;
	}
	return true;
}

// Called before quitting
bool W2_Scene::CleanUp()
{
	LOG("Freeing scene");
	//app->fonts->Unload(font);
	app->map->CleanUp(); 
	app->entityManager->CleanUp(); 
	app->physics->Disable();

	app->tex->UnLoad(npcPopUpTexture);
	app->tex->UnLoad(uiSpriteTexture);
	app->tex->UnLoad(questUiTexture);
	app->tex->UnLoad(lvlupTexture);
	app->tex->UnLoad(eKeyTexture);
	app->tex->UnLoad(chestTexture);

	return true;
}

//Toggles god mode on and off when the F10 key is pressed. When god mode is on, the camera follows the player's position without any boundaries.
void W2_Scene::GodMode()
{
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godMode)
		{
			godMode = false;
		}
		else
		{
			godMode = true;
		}
	}
}

//Updates the camera position based on the player's position. If god mode is on, the camera follows the player's position without any boundaries. If god mode is off, the camera follows the player's position while respecting the game's boundaries.
void W2_Scene::Camera()
{
	if (godMode || !CheckInsideBoundaries())
	{
		app->render->FollowObject(-(int)player->position.x, -(int)player->position.y - 35,
			app->render->camera.w / 2, app->render->camera.h / 2);
	}
	else
	{
		app->render->FollowObjectRespectBoundaries(-(int)player->position.x, -(int)player->position.y - 35,
			app->render->camera.w / 2, app->render->camera.h / 2, -4394, -93, -3674, -1212);
	}

}

bool W2_Scene::CheckInsideBoundaries()
{	
	bool insideX = (player->position.x == clamp(player->position.x, 93, 4394+(1920)));
	bool insideY = (player->position.y == clamp(player->position.y, 1212, 3674+1080));
	
	if (insideX && insideY)
	{
		return true;
	}
	
	return false;
}

//Runs a dialogue tree for a specific NPC, identified using a ColliderType enum. This function delegates the NPC specific behavior to other functions based on the enum passed in.
void W2_Scene::RunDialogueTree(ColliderType NPC)
{
	switch (NPC)
	{
	case ColliderType::PIGS:
		dialogue = pigsTree->Run();

		for (auto& text : dialogue)
		{
			std::cout << text << std::endl;
		}
		
		if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
		{
			UpdateDialogueTree(3);
		}

		if (dialogue.empty() && !pigsDefeated)
		{
			dialogue.push_back("Little and Middle pig : We're pigs and we do as we please. What makes you think we care about what you think or try? Get ready.");
		}
		break;
	case ColliderType::WOLF:
		dialogue = wolfTree->Run();

		break;

	case ColliderType::ZORRO:
		dialogue = zorroTree->Run();

		if (dialogue.empty())
		{
			dialogue.push_back("If you keep going this way, you will come across a cave, full of challenges and mysteries.");
		}
		for (auto& text : dialogue)
		{
			std::cout << text << std::endl;
		}

		break;
	default:
		break;
	}
}

//Updates the dialogue tree based on the player's response to a dialogue prompt. The dialogue tree to update is selected based on the type of NPC the player last interacted
//with, as determined by the player's lastCollision variable. 
void W2_Scene::UpdateDialogueTree(int option)
{
	if (1 >= option <= 4)
	{
		switch (app->w2_scene->player->lastCollision)
		{
		case ColliderType::PIGS:
			pigsTree->Update(option);
			numTimesPigsDialogueTriggered++;
			break;

		case ColliderType::WOLF:
			wolfTree->Update(option);
			break;
		default:
			break;
		}
	}



}


//Create Tree Dialogues
void W2_Scene::CreateDialogue()
{//Wolfs


	if (!pigsDefeated)
	{
		// - Pigs Pre Battle
	//3rd level
		auto secondOption1PT = std::make_shared<DialogueNode>();
		secondOption1PT->SetText("OMGGG!");

		auto secondOption2PT = std::make_shared<DialogueNode>();
		secondOption2PT->SetText("How could you do that? You're monsters and you'll be the next ones to become bacon.");

		auto secondOption3PT = std::make_shared<DialogueNode>();
		secondOption3PT->SetText("What guarantees that you won't do the same to us? I'll end you (with a trembling voice).");

		auto secondOption4PT = std::make_shared<DialogueNode>();
		secondOption4PT->SetText("Whatever, let's just move on and get this over with.");

		//2nd level
		auto PigsToOptionPT = std::make_shared<DialogueNode>();
		PigsToOptionPT->SetText("Little  pig: Oh, don't worry about him. He was just an obstacle in our way to freedom. Middle pig: Yeah, after all, we were very hungry.");
		PigsToOptionPT->AddChild(secondOption1PT);
		PigsToOptionPT->AddChild(secondOption2PT);
		PigsToOptionPT->AddChild(secondOption3PT);
		PigsToOptionPT->AddChild(secondOption4PT);

		//1rst level
		auto firstOption1PT = std::make_shared<DialogueNode>();
		firstOption1PT->SetText("What happened here? The houses are destroyed.");
		firstOption1PT->AddChild(PigsToOptionPT);

		auto firstOption2PT = std::make_shared<DialogueNode>();
		firstOption2PT->SetText("What the hell did you do to your older brother, you despicable pigs?");
		firstOption2PT->AddChild(PigsToOptionPT);

		auto firstOption3PT = std::make_shared<DialogueNode>();
		firstOption3PT->SetText("W-where is your older brother? Will we find him in the portal?");
		firstOption3PT->AddChild(PigsToOptionPT);

		auto firstOption4PT = std::make_shared<DialogueNode>();
		firstOption4PT->SetText("Fine, fine, I get it, more trouble. Because I can't have a peaceful life.");
		firstOption4PT->AddChild(PigsToOptionPT);

		//Root
		auto firstNodePigs = std::make_shared<DialogueNode>();
		firstNodePigs->SetText("Little  pig: (with a sinister smile) Hi, friend. What brings you here?. Middle pig: (laughing) Looks like you arrived at the wrong time.");
		firstNodePigs->AddChild(firstOption1PT);
		firstNodePigs->AddChild(firstOption2PT);
		firstNodePigs->AddChild(firstOption3PT);
		firstNodePigs->AddChild(firstOption4PT);
		firstNodePigs->ActivateNode();

		//Tree
		pigsTree = std::make_shared<DialogueTree>();
		pigsTree->SetRoot(firstNodePigs);
	}
	else
	{
		auto firstNodeWolf = std::make_shared<DialogueNode>();
		firstNodeWolf->SetText("You will pay for this, Timmy. And you, you pathetic pigs, couldn't even defeat him. You're all worthless.");
		firstNodeWolf->ActivateNode();

		wolfTree = std::make_shared<DialogueTree>();
		wolfTree->SetRoot(firstNodeWolf);

		//PigsAfterCombat:
		//1rst level
		auto firstOption1AC = std::make_shared<DialogueNode>();
		firstOption1AC->SetText("Thank you for your apology. We can work together to stop the wolf and avenge your brother.");

		auto firstOption2AC = std::make_shared<DialogueNode>();
		firstOption2AC->SetText("You better not betray us again or you'll regret it. But for now, welcome to the team.");

		auto firstOption3AC = std::make_shared<DialogueNode>();
		firstOption3AC->SetText("I don't know if I can trust you, but I need all the help I can get. Welcome to the group.");

		auto firstOption4AC = std::make_shared<DialogueNode>();
		firstOption4AC->SetText("Whatever, I don't really care. As long as you don't get in my way, you can join us.");

		auto firstNodePigsAC = std::make_shared<DialogueNode>();
		firstNodePigsAC->SetText("SmallerMiddle pig: I'm sorry, Timmy. I don't know how we could do such a thing. We were carried away by the darkness. Little pig: (nodding) Yes, I'm so sorry. But now we want to help you. We know we can't bring our brother back to life, but we can help you avenge him.");
		firstNodePigsAC->AddChild(firstOption1AC);
		firstNodePigsAC->AddChild(firstOption2AC);
		firstNodePigsAC->AddChild(firstOption3AC);
		firstNodePigsAC->AddChild(firstOption4AC);
		firstNodePigsAC->ActivateNode();

		pigsTree = std::make_shared<DialogueTree>();
		pigsTree->SetRoot(firstNodePigsAC);
	}

	auto zorroNode = std::make_shared<DialogueNode>();
	zorroNode->SetText("If you keep going this way, you will come across a cave, full of challenges and mysteries. Help Me!");
	zorroNode->ActivateNode();
	zorroTree = std::make_shared<DialogueTree>();
	zorroTree->SetRoot(zorroNode);

}

bool W2_Scene::LoadState(pugi::xml_node& data)
{
	loadPlayerPosX = data.child("player").attribute("x").as_int();
	loadPlayerPosY = data.child("player").attribute("y").as_int();

	if (active)
	{
		player->ChangePosition(loadPlayerPosX, loadPlayerPosY);
	}

	pugi::xml_node battleInfo = data.parent().child("BattleInfo");
	pigsDefeated = battleInfo.attribute("isPigDefeated").as_bool();

	return true;
}

bool W2_Scene::SaveState(pugi::xml_node& data)
{
	if (active) {
		pugi::xml_node playerNode = data.append_child("player");

		// If door, save mes lluny
		if (app->uiModule->doorPlayerPosition)
		{
			playerNode.append_attribute("x") = player->position.x;
			playerNode.append_attribute("y") = player->position.y + 75;
			app->uiModule->doorPlayerPosition = false;
		}
		else {
			playerNode.append_attribute("x") = player->position.x;
			playerNode.append_attribute("y") = player->position.y;
		}
	}
	

	return true;
}


//This function swaps after 2sec from Scene to SceneBattle/LRRHCombat If Player has triggered the dialogue with AngryVillager/LRRH and they haven't been defeated before
void W2_Scene::MoveToBattleFromDialogue()
{
	if (numTimesPigsDialogueTriggered == 1 && !pigsDefeated)
	{
		timerToPigsCombat.Start(3.0f);
		numTimesPigsDialogueTriggered = 0;
	}

	if (timerToPigsCombat.Test() == estadoTimerP::FIN)
	{
		//Teleportar a GameScene::Pigcombat
		app->sceneManager->LoadScene(GameScene::COMBATOINK);
	}



}


// A function to draw the current quest on the screen
void W2_Scene::drawQuest(int posX, int posY) {

	questText = questList[currentQuestIndex].description;

	SDL_Rect rect = { 0, 0, 280, 20 };

	textDialogue = app->fonts->LoadRenderedParagraph(rect, app->fonts->gameFont, questText, { 0,0,0 }, 280);

	app->render->DrawTexture(textDialogue, posX, posY, &rect);
}

// A function to move to the next quest
void W2_Scene::nextQuest() {
	currentQuestIndex++;
	if (currentQuestIndex >= questList.size()) {
		// If we've reached the end of the quest list, wrap around to the beginning
		currentQuestIndex = 0;
	}
}

// Code to Load Chests variables, encapsulated. It is called in LoadState() 
void W2_Scene::LoadChests(pugi::xml_node& data)
{
	chest4->isPicked = data.child("chest4").attribute("isPicked").as_bool();
	chest5->isPicked = data.child("chest5").attribute("isPicked").as_bool();
	chest6->isPicked = data.child("chest6").attribute("isPicked").as_bool();

}
