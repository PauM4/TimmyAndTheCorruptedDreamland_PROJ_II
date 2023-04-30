#include "BattleManager.h"

#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "PathFinding.h"
#include "GuiButton.h"
#include "Defs.h"
#include "Physics.h"
#include "Log.h"

BattleManager::BattleManager(bool isActive) : Module(isActive) {

	name.Create("battleManager");
}

// Destructor
BattleManager::~BattleManager() {}

bool BattleManager::Awake(pugi::xml_node& config) {


	return true;
}

bool BattleManager::Start() {

	MakeTurnList();
	currentTurn = turnList.start->data;
	origin = currentTurn->tilePos;

	battleState = BattleState::THINKING;
	return true;
}

bool BattleManager::PreUpdate() {

	MousePosition();


	return true;
}

bool BattleManager::Update(float dt) {

	switch (battleState)
	{
	case BattleState::UNKNOWN:
		break;
	case BattleState::THINKING:

		targets.Clear();
		actionArea.Clear();
		switch (buttonPressed)
		{
		case CombatButtons::ATTACK:


			actionType = ActionType::ATTACK;


			break;

		case CombatButtons::ABILITY:

			actionType = ActionType::ABILITY;

			break;

		case CombatButtons::MOVE:

			actionType = ActionType::MOVE;
			break;

		case CombatButtons::END:

			actionType = ActionType::END_TURN;

			UpdateTurnList();

			break;

		case CombatButtons::NONE:

			actionType = ActionType::UNKNOWN;

			break;
		}
		break;
	case BattleState::SELCETED:

		origin = currentTurn->tilePos;

		if (actionType == ActionType::MOVE) {

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				if (app->pathfinding->IsWalkable(origin) && combatMap[mouseTile.x][mouseTile.y].inRange == true && combatMap[mouseTile.x][mouseTile.y].character == false) {
					length = app->pathfinding->CreatePath(origin, mouseTile);
					destination.x = mouseTile.x;
					destination.y = mouseTile.y;
					moveanim = true;
					currentTurn->UseStamina(3);
					battleState = BattleState::INACTION;
				}
			}
		}
		else {
			
			GetActionArea(currentTurn, actionType);
			SelectTargets();

			for (int i = 0; i < targets.Count(); i++) {


				if (targets.At(i)->data->tilePos == mouseTile) {
					if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {



						targets.At(i)->data->health = targets.At(i)->data->health - (currentTurn->attack - targets.At(i)->data->defense);
						
						currentTurn->UseStamina(5);
						battleState = BattleState::INACTION;

					}
				}
			}
		}

		break;
	case BattleState::INACTION:

		if (actionType == ActionType::MOVE) {
			
			if (pathIndex != length) {

				length = app->pathfinding->CreatePath(origin, destination);
				Move(pathIndex, length);
			}
			else
			{
				if (currentTurn->tilePos == destination) {

				
					destination = iPoint(0, 0);
					length = 1;
					pathIndex = 1;
					app->pathfinding->ClearLastPath();
					battleState = BattleState::THINKING;
					UpdateTurnList();
				}
			}

		}
		else {

			battleState = BattleState::THINKING;
			UpdateTurnList();

		}

		break;
	case BattleState::WIN:
		break;
	case BattleState::LOSE:
		break;
	default:
		break;
	}
	

		

	
	


	return true;
}

bool BattleManager::PostUpdate() {

	if (battleState == BattleState::SELCETED) {

		DisplayArea(actionType);

    }



	


	DisplayTurnList();
	return true;
}

bool BattleManager::CleanUp() {


	return true;
}

Entity* BattleManager::GetCurrentTurn() { return currentTurn;}



bool BattleManager::OnGuiMouseClickEvent(GuiControl* control)
{
	LOG("Event by %d ", control->id);

	if (battleState == BattleState::THINKING) {
		switch (control->id)
		{
		case 16:
			buttonPressed = CombatButtons::ATTACK;
			break;

		case 17:
			buttonPressed = CombatButtons::ABILITY;
			break;

		case 18:
			buttonPressed = CombatButtons::MOVE;
			break;

		case 19:
			buttonPressed = CombatButtons::END;
			return true;
		}

		battleState = BattleState::SELCETED;
	}
	return true;

}


// Loads combat map from Map module using GID tile metadata
bool BattleManager::MakeCombatMap() {

	bool ret = true;

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 9; j++) {

			combatMap[i][j].x = i;
			combatMap[i][j].y = j;
			combatMap[i][j].inRange = false;
			combatMap[i][j].type = (TILE_TYPE)app->map->metadataLayer[i][j];
		}
	}

	return ret;
}

bool BattleManager::GetActionArea(Entity* character, ActionType type) {

	switch (type) {
	case ActionType::MOVE:
		//actionArea = character.attackArea;

		break;
	case ActionType::ATTACK:
		//actionArea = character.abiltyArea;
		for (int i = 1; i <= character->AttArea; i++) {
			if (combatMap[character->tilePos.x + i][character->tilePos.y].type == TILE_TYPE::FLOOR) {
				actionArea.Add(&combatMap[character->tilePos.x + i][character->tilePos.y]);
			}
			if (combatMap[character->tilePos.x - i][character->tilePos.y].type == TILE_TYPE::FLOOR) {
				actionArea.Add(&combatMap[character->tilePos.x - i][character->tilePos.y]);
			}
			if (combatMap[character->tilePos.x][character->tilePos.y + i].type == TILE_TYPE::FLOOR) {
				actionArea.Add(&combatMap[character->tilePos.x][character->tilePos.y + i]);
			}
			if (combatMap[character->tilePos.x][character->tilePos.y - i].type == TILE_TYPE::FLOOR) {
				actionArea.Add(&combatMap[character->tilePos.x][character->tilePos.y - i]);
			}
		}
		break;
	case ActionType::ABILITY:
		//actionArea = character.moveArea;


		for (int i = 0; i <= character->Ab1Area; i++) {
			for (int j = 0; j <= character->Ab1Area - i; j++) {
				if (combatMap[character->tilePos.x + j][character->tilePos.y + i].type == TILE_TYPE::FLOOR) {
					actionArea.Add(&combatMap[character->tilePos.x + j][character->tilePos.y + i]);
				}
				if (combatMap[character->tilePos.x - j][character->tilePos.y + i].type == TILE_TYPE::FLOOR) {
					actionArea.Add(&combatMap[character->tilePos.x - j][character->tilePos.y + i]);
				}
				if (combatMap[character->tilePos.x - j][character->tilePos.y - i].type == TILE_TYPE::FLOOR) {
					actionArea.Add(&combatMap[character->tilePos.x - j][character->tilePos.y - i]);
				}
				if (combatMap[character->tilePos.x + j][character->tilePos.y - i].type == TILE_TYPE::FLOOR) {
					actionArea.Add(&combatMap[character->tilePos.x + j][character->tilePos.y - i]);
				}
			}

		}
		break;
	default:
		break;
	}

	return true;
}

bool BattleManager::MousePosition() {
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);


	mouseTile = app->map->WorldToMap(mouseX - app->render->camera.x, mouseY - app->render->camera.y);
	iPoint highlightedTileWorld = app->map->MapToWorld(mouseTile.x, mouseTile.y);
	if (app->pathfinding->IsWalkable(mouseTile) && combatMap[mouseTile.x][mouseTile.y].character != false) {
		app->render->DrawRectangle({ highlightedTileWorld.x, highlightedTileWorld.y, 120, 120 }, 0, 143, 57, 100, true);

	}

}
bool BattleManager::Move(int pathindex, int length) {

	iPoint dist;
	fPoint pixelPosition;
	fPoint finalPosition;
	float distance;
	b2Vec2 vel = b2Vec2(0, 0);

	const DynArray<iPoint>* lastpath = app->pathfinding->GetLastPath();


	pixelPosition.x = lastpath->At(pathIndex)->x * app->map->mapData.tileWidth;
	pixelPosition.y = lastpath->At(pathIndex)->y * app->map->mapData.tileHeight;

	finalPosition.x = lastpath->At(length - 1)->x * app->map->mapData.tileWidth;
	finalPosition.x = lastpath->At(length - 1)->x * app->map->mapData.tileWidth;


	dist.x = pixelPosition.x - currentTurn->position.x;
	dist.y = pixelPosition.y - currentTurn->position.y;


	xDir = 0;
	yDir = 0;
	xDir = (dist.x > 0) ? 1 : -1;
	yDir = (dist.y > 0) ? 1 : -1;
	if (dist.x == 0) {
		xDir = 0;
	}
	if (dist.y == 0) {
		yDir = 0;
	}
	if (dist.x == 0 && dist.y == 0) {
		pathIndex++;

	}
	else if (abs(dist.x) > 0) {
		vel.x = 5 * xDir;

	}
	else if (abs(dist.y) > 0) {
		vel.y = 5 * yDir;

	}

	currentTurn->position.x = currentTurn->position.x + vel.x;
	currentTurn->position.y = currentTurn->position.y + vel.y;

	return true;
}
bool BattleManager::AddCharacter(Entity* character, int x, int y, bool isEnemy) {

	if (isEnemy) enemies.Add(character);
	else allies.Add(character);

	combatMap[x][y].character = character;

	return true;
}

bool BattleManager::MakeTurnList() {

	List<Entity*> auxList;

	//Fill auxList
	for (ListItem<Entity*>* allyItem = allies.start; allyItem != NULL; allyItem = allyItem->next) {
		auxList.Add(allyItem->data);
	}
	for (ListItem<Entity*>* enemyItem = enemies.start; enemyItem != NULL; enemyItem = enemyItem->next) {
		auxList.Add(enemyItem->data);
	}

	//Sort auxList into turnList based on Entity->speed
	while (auxList.Count() > 0) {
		ListItem<Entity*>* auxIndex = NULL;

		for (ListItem<Entity*>* auxItem = auxList.start; auxItem != NULL; auxItem = auxItem->next) {
			if (auxItem->data->speed > auxIndex->data->speed || auxIndex == NULL) {
				auxIndex = auxItem;
			}
		}

		auxList.Del(auxIndex);
		turnList.Add(auxIndex->data);
		auxIndex = NULL;
	}
	
	return true;
}
bool BattleManager::SelectTargets() {


	ListItem<TileData*>* tileListItem;
	


	for (tileListItem = actionArea.start; tileListItem != NULL; tileListItem = tileListItem->next) {

		if (tileListItem->data->character != NULL && tileListItem->data->character->isEnemy==true && currentTurn->isEnemy==false) {

			targets.Add(tileListItem->data->character);
		}
		else if (tileListItem->data->character != NULL && tileListItem->data->character->isEnemy == false && currentTurn->isEnemy == true) {

			targets.Add(tileListItem->data->character);
		}

	}

	return true;
}
bool BattleManager::UpdateTurnList() {

	ListItem<Entity*>* auxItem;
	auxItem = turnList.start;

	turnList.Del(auxItem);
	turnList.Add(auxItem->data);

	currentTurn = turnList.start->data;

	return true;
}

bool BattleManager::DisplayTurnList() {

	ListItem<Entity*>* listItem;

	for (listItem = turnList.start; listItem != NULL; listItem = listItem->next) {
		//call icon draw function in entity. To yet be implemented
	}


	return true;
}

bool BattleManager::DisplayArea(ActionType type) {

	bool ret = true;

	ListItem<TileData*>* tileListItem;
	tileListItem = actionArea.start;

	uint color[3];

	switch (type)
	{
	case ActionType::MOVE:
		color[0] = 255;
		color[1] = 0;
		color[2] = 0;
		break;
	case ActionType::ATTACK:
		color[0] = 0;
		color[1] = 255;
		color[2] = 0;
		break;
	case ActionType::ABILITY:
		color[0] = 0;
		color[1] = 0;
		color[2] = 255;
		break;
	default:
		break;
	}

	while (tileListItem != NULL) {

		iPoint pos = app->map->MapToWorld(tileListItem->data->x, tileListItem->data->y);
		app->render->DrawRectangle({ pos.x,pos.y,app->map->mapData.tileWidth,app->map->mapData.tileHeight }, color[0], color[1], color[2], 100);

		tileListItem = tileListItem->next;
	}

	return ret;
}

bool BattleManager::ApplyAction(Entity* character, ActionType type) {

	for (ListItem<Entity*>* targetItem = targets.start; targetItem != NULL; targetItem = targetItem->next) {
		switch (type) {
		case ActionType::ATTACK:
			targetItem->data->TakeDamage(character->attack);
			break;
		case ActionType::ABILITY:
			targetItem->data->TakeDamage(character->Ab1Power);
			break;
		default:
			break;
		}
	}

	return true;
}




