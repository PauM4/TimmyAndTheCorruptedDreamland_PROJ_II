#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "UIModule.h"

#include "GuiButton.h"
#include "Item.h"
#include "Npc.h"
#include "DialogueTree.h"
#include "UriBehaviorTree.h"
#include "Physics.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool isActive);

	// Destructor
	virtual ~Scene();

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

	std::string LastTextNPC(ColliderType NPC);
	std::string LastTextAngryVillager(std::string);
	std::string LastTextTalismanVillager(std::string);
	std::string LastTextGrandmaVillager(std::string);
	std::string LastTextLittleRedVillager(std::string);

private:

	void Camera();
	void GodMode();
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

public:

	Player* player;
	Npc* npc1;
	//Item* item1;

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

	std::shared_ptr<DialogueTree> angryVillagerTree, angryVillagerTreePT, 
		talismanVillagerTree, littleRedTree, grandmaTree;

	std::vector<std::string> dialogue;

	void Prueba();

	int pruebaj = 0;

	bool godMode;

};

#endif // __SCENE_H__