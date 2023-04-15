#ifndef __SCENEMAINMENU_H__
#define __SCENEMAINMENU_H__

#include "Module.h"

struct SDL_Texture;

class SceneMainMenu : public Module
{
public:

	SceneMainMenu(bool isActive);

	// Destructor
	virtual ~SceneMainMenu();

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


public:
	
	SDL_Texture* mainMenu_image;

	// Window width and height
	int w, h;

private:

};

#endif // __SCENEMAINMENU_H__