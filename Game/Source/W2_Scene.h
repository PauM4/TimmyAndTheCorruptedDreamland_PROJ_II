#ifndef __W2_SCENE_H__
#define __W2_SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Door.h"
#include "Npc.h"

#include "UIModule.h"
#include "GuiButton.h"
#include "DialogueTree.h"
#include "UriBehaviorTree.h"
#include "Physics.h"

struct SDL_Texture;

class W2_Scene : public Module
{
public:

	W2_Scene(bool isActive);

	// Destructor
	virtual ~W2_Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	void CreateDialogue();

	void RunDialogueTree(ColliderType NPC);

	void UpdateDialogueTree(int opt);

	void AppearDialogue();

	std::vector<std::string> GetDialogue2() { return dialogue; }


	ColliderType GetPlayerLastCollision() { return player->lastCollision; }

private:

	void Camera();
	void GodMode();
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);


public:

	Player* player;
	Npc* npc1;
	List<Door*> doors;


	// Load things
	int loadPlayerPosX;
	int loadPlayerPosY;

	// New Game things
	bool isNewGame;

	SDL_Texture* npcPopUpTexture;
	SDL_Texture* uiSpriteTexture;

private:

	SString mapName;
	SString mapFolder;


	// L12: Debug pathfing
	iPoint origin;
	bool originSelected = false;

	//Fonts
	int font;

	bool pauseMenuActive;
	bool exitButtonBool;

	std::shared_ptr<DialogueTree> pigsBeforeCombatTree, pigsAfterCombatTree, wolfTree;

	std::vector<std::string> dialogue;

	void Prueba();

	int pruebaj = 0;

	bool godMode;


};

#endif // __W2_SCENE_H__