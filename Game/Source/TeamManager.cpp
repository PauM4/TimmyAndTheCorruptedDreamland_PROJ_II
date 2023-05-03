#include "TeamManager.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "Point.h"
#include "EntityManager.h"
#include "Timmy.h"
#include "Bunny.h"
TeamManager::TeamManager(bool isActive) : Module (isActive)
{
	name.Create("teamManager");

}

TeamManager::~TeamManager() {

}

bool TeamManager::Awake(pugi::xml_node& config)
{
	
	//Load from xml
	if (config.parent().child("timmy")) {
		timmy = (Timmy*)app->entityManager->CreateEntity(EntityType::TIMMY);
		timmy->stats = config.parent().child("timmy");
	}
	if (config.parent().child("bunny")) {
		bunny = (Bunny*)app->entityManager->CreateEntity(EntityType::BUNNY);
		bunny->stats = config.parent().child("bunny");
	}
	if (config.parent().child("lrrh")) {
		lrrh = (Lrrh*)app->entityManager->CreateEntity(EntityType::LRRH);
		lrrh->stats = config.parent().child("lrrh");
	}
	if (config.parent().child("littlePig")) {
		littlepig = (LittlePig*)app->entityManager->CreateEntity(EntityType::LPIG);
		littlepig->stats = config.parent().child("littlePig");
	}
	if (config.parent().child("middlePig")) {
		middlepig = (MiddlePig*)app->entityManager->CreateEntity(EntityType::MPIG);
		middlepig->stats = config.parent().child("middlePig");
	}
	if (config.parent().child("peter")) {
		peter = (Peter*)app->entityManager->CreateEntity(EntityType::PETER);
		peter->stats = config.parent().child("peter");
	}
	istimmyplayable = config.child("playable").attribute("istimmyplayable").as_bool();
	isbunnyplayable = config.child("playable").attribute("isbunnyplayable").as_bool();
	islrrhplayable = config.child("playable").attribute("islrrhplayable").as_bool();
	islilpigplayable = config.child("playable").attribute("islilpigplayable").as_bool();
	ismidpigplayable = config.child("playable").attribute("ismidpigplayable").as_bool();
	ispeterplayable = config.child("playable").attribute("ispeterplayable").as_bool();

	IsTimmyOnTeam = config.child("onteam").attribute("IsTimmyOnTeam").as_bool();
	IsBunnyOnTeam = config.child("onteam").attribute("IsBunnyOnTeam").as_bool();
	IsLrrhOnTeam = config.child("onteam").attribute("IsLrrhOnTeam").as_bool();
	IsLilPigOnTeam = config.child("onteam").attribute("IsLilPigOnTeam").as_bool();
	IsMidPigOnTeam = config.child("onteam").attribute("IsMidPigOnTeam").as_bool();
	IsPeterOnTeam = config.child("onteam").attribute("IsPeterOnTeam").as_bool();


	if (config.child("item").child("yoyo")) {
		pugi::xml_node newnode = config.child("item").child("yoyo");
		yoyo.ininventory = newnode.attribute("ininventory").as_bool();
		yoyo.type = newnode.attribute("type").as_int();
		yoyo.weaponuser = newnode.attribute("weaponuser").as_int();
		yoyo.character = newnode.attribute("character").as_int();
		yoyo.name = newnode.attribute("name").as_string();
		yoyo.defense = newnode.attribute("defense").as_int();
		yoyo.magic = newnode.attribute("magic").as_int();
		yoyo.speed = newnode.attribute("speed").as_int();
		yoyo.movement = newnode.attribute("movement").as_int();
		yoyo.attack = newnode.attribute("attack").as_int();
		yoyo.AttArea = newnode.attribute("AttArea").as_int();
		yoyo.Ab1Power = newnode.attribute("Ab1Power").as_int();
		yoyo.Ab2Power = newnode.attribute("Ab2Power").as_int();
		yoyo.Ab1Area = newnode.attribute("Ab1Area").as_int();
		yoyo.Ab2Area = newnode.attribute("Ab2Area").as_int();
		yoyo.healingpower = newnode.attribute("healingpower").as_int();
	}
	if (config.child("item").child("handsxd")) {
		pugi::xml_node newnode = config.child("item").child("handsxd");
		handsxd.ininventory = newnode.attribute("ininventory").as_bool();
		handsxd.type = newnode.attribute("type").as_int();
		handsxd.weaponuser = newnode.attribute("weaponuser").as_int();
		handsxd.character = newnode.attribute("character").as_int();
		handsxd.name = newnode.attribute("name").as_string();
		handsxd.defense = newnode.attribute("defense").as_int();
		handsxd.magic = newnode.attribute("magic").as_int();
		handsxd.speed = newnode.attribute("speed").as_int();
		handsxd.movement = newnode.attribute("movement").as_int();
		handsxd.attack = newnode.attribute("attack").as_int();
		handsxd.AttArea = newnode.attribute("AttArea").as_int();
		handsxd.Ab1Power = newnode.attribute("Ab1Power").as_int();
		handsxd.Ab2Power = newnode.attribute("Ab2Power").as_int();
		handsxd.Ab1Area = newnode.attribute("Ab1Area").as_int();
		handsxd.Ab2Area = newnode.attribute("Ab2Area").as_int();
		handsxd.healingpower = newnode.attribute("healingpower").as_int();
	}
	if (config.child("item").child("bow")) {
		pugi::xml_node newnode = config.child("item").child("bow");
		bow.ininventory = newnode.attribute("ininventory").as_bool();
		bow.type = newnode.attribute("type").as_int();
		bow.weaponuser = newnode.attribute("weaponuser").as_int();
		bow.character = newnode.attribute("character").as_int();
		bow.name = newnode.attribute("name").as_string();
		bow.defense = newnode.attribute("defense").as_int();
		bow.magic = newnode.attribute("magic").as_int();
		bow.speed = newnode.attribute("speed").as_int();
		bow.movement = newnode.attribute("movement").as_int();
		bow.attack = newnode.attribute("attack").as_int();
		bow.AttArea = newnode.attribute("AttArea").as_int();
		bow.Ab1Power = newnode.attribute("Ab1Power").as_int();
		bow.Ab2Power = newnode.attribute("Ab2Power").as_int();
		bow.Ab1Area = newnode.attribute("Ab1Area").as_int();
		bow.Ab2Area = newnode.attribute("Ab2Area").as_int();
		bow.healingpower = newnode.attribute("healingpower").as_int();
	}
	if (config.child("item").child("club")) {
		pugi::xml_node newnode = config.child("item").child("club");
		club.ininventory = newnode.attribute("ininventory").as_bool();
		club.type = newnode.attribute("type").as_int();
		club.weaponuser = newnode.attribute("weaponuser").as_int();
		club.character = newnode.attribute("character").as_int();
		club.name = newnode.attribute("name").as_string();
		club.defense = newnode.attribute("defense").as_int();
		club.magic = newnode.attribute("magic").as_int();
		club.speed = newnode.attribute("speed").as_int();
		club.movement = newnode.attribute("movement").as_int();
		club.attack = newnode.attribute("attack").as_int();
		club.AttArea = newnode.attribute("AttArea").as_int();
		club.Ab1Power = newnode.attribute("Ab1Power").as_int();
		club.Ab2Power = newnode.attribute("Ab2Power").as_int();
		club.Ab1Area = newnode.attribute("Ab1Area").as_int();
		club.Ab2Area = newnode.attribute("Ab2Area").as_int();
		club.healingpower = newnode.attribute("healingpower").as_int();
	}

	
	statslist.Add(&timmystats);
	statslist.Add(&bunnystats);
	statslist.Add(&lrrhstats);
	statslist.Add(&lilpigstats);
	statslist.Add(&midpigstats);
	statslist.Add(&peterstats);

	for (int i = 0; i < statslist.Count(); i++) {

		statslist.At(i)->data->character = i+1;
		statslist.At(i)->data->defense = 0;
		statslist.At(i)->data->magic = 0;
		statslist.At(i)->data->speed = 0;
		statslist.At(i)->data->movement = 0;
		statslist.At(i)->data->attack = 0;
		statslist.At(i)->data->AttArea = 0;
		statslist.At(i)->data->Ab1Power = 0;
		statslist.At(i)->data->Ab2Power = 0;
		statslist.At(i)->data->Ab1Area = 0;
		statslist.At(i)->data->Ab2Area = 0;
		statslist.At(i)->data->healingpower = 0;

	}
	
	app->entityManager->Awake(config);

	return true;
}

bool TeamManager::Start()
{


	return true;
}

bool TeamManager::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

		ispeterplayable = true;
		IsPeterOnTeam = true;
		peterstats.attack = 3;
		app->SaveGameRequest();

	}
	peter->attack;
	return true;

}

bool TeamManager::PostUpdate()
{

	return true;
}

bool TeamManager::CleanUp()
{
	characters.Clear();
	team.Clear();
	inventory.Clear();
	equipment.Clear();
	statslist.Clear();
	timmy->CleanUp();
	bunny->CleanUp();
	lrrh->CleanUp();
	littlepig->CleanUp();
	middlepig->CleanUp();
	peter->CleanUp();
	return true;
}
bool TeamManager::LoadState(pugi::xml_node& data)
{
	
	//Load unlocked characters
	istimmyplayable = data.child("playable").attribute("istimmyplayable").as_bool();
	isbunnyplayable = data.child("playable").attribute("isbunnyplayable").as_bool();
	islrrhplayable = data.child("playable").attribute("islrrhplayable").as_bool();
	islilpigplayable = data.child("playable").attribute("islilpigplayable").as_bool();
	ismidpigplayable = data.child("playable").attribute("ismidpigplayable").as_bool();
	ispeterplayable = data.child("playable").attribute("ispeterplayable").as_bool();
	//Load characters the team
	IsTimmyOnTeam = data.child("onteam").attribute("IsTimmyOnTeam").as_bool();
	IsBunnyOnTeam = data.child("onteam").attribute("IsBunnyOnTeam").as_bool();
	IsLrrhOnTeam = data.child("onteam").attribute("IsLrrhOnTeam").as_bool();
	IsLilPigOnTeam = data.child("onteam").attribute("IsLilPigOnTeam").as_bool();
	IsMidPigOnTeam = data.child("onteam").attribute("IsMidPigOnTeam").as_bool();
	IsPeterOnTeam = data.child("onteam").attribute("IsPeterOnTeam").as_bool();
	//Add characters and team to the lists
	characters.Clear();
	team.Clear();
	characters.Add(timmy);
	characters.Add(bunny);
	if (IsTimmyOnTeam == true) {
		team.Add(timmy);
	}
	if (IsBunnyOnTeam == true) {
		team.Add(bunny);
	}
	if (islrrhplayable == true) {
		characters.Add(lrrh);
		if (IsLrrhOnTeam == true) {
			team.Add(lrrh);
		}
	}
	if (islilpigplayable == true) {
		characters.Add(littlepig);
		if (IsLilPigOnTeam == true) {
			team.Add(littlepig);
		}
	}
	if (ismidpigplayable == true) {
		characters.Add(middlepig);
		if (IsMidPigOnTeam == true) {
			team.Add(middlepig);
		}
	}
	if (ispeterplayable == true) {
		characters.Add(peter);
		if (IsPeterOnTeam == true) {
			team.Add(peter);
		}
	}
	//Load Stats
	pugi::xml_node statsnode = data.child("stats");
	timmystats.defense = statsnode.child("timmy").attribute("defense").as_int();
	timmystats.magic = statsnode.child("timmy").attribute("magic").as_int();
	timmystats.speed = statsnode.child("timmy").attribute("speed").as_int();
	timmystats.movement = statsnode.child("timmy").attribute("movement").as_int();
	timmystats.attack = statsnode.child("timmy").attribute("attack").as_int();
	timmystats.AttArea = statsnode.child("timmy").attribute("AttArea").as_int();
	timmystats.Ab1Power = statsnode.child("timmy").attribute("Ab1Power").as_int();
	timmystats.Ab2Power = statsnode.child("timmy").attribute("Ab2Power").as_int();
	timmystats.Ab1Area = statsnode.child("timmy").attribute("Ab1Area").as_int();
	timmystats.Ab2Area = statsnode.child("timmy").attribute("Ab2Area").as_int();
	timmystats.healingpower = statsnode.child("timmy").attribute("healingpower").as_int();

	bunnystats.defense = statsnode.child("bunny").attribute("defense").as_int();
	bunnystats.magic = statsnode.child("bunny").attribute("magic").as_int();
	bunnystats.speed = statsnode.child("bunny").attribute("speed").as_int();
	bunnystats.movement = statsnode.child("bunny").attribute("movement").as_int();
	bunnystats.attack = statsnode.child("bunny").attribute("attack").as_int();
	bunnystats.AttArea = statsnode.child("bunny").attribute("AttArea").as_int();
	bunnystats.Ab1Power = statsnode.child("bunny").attribute("Ab1Power").as_int();
	bunnystats.Ab2Power = statsnode.child("bunny").attribute("Ab2Power").as_int();
	bunnystats.Ab1Area = statsnode.child("bunny").attribute("Ab1Area").as_int();
	bunnystats.Ab2Area = statsnode.child("bunny").attribute("Ab2Area").as_int();
	bunnystats.healingpower = statsnode.child("bunny").attribute("healingpower").as_int();

	lrrhstats.defense = statsnode.child("lrrh").attribute("defense").as_int();
	lrrhstats.magic = statsnode.child("lrrh").attribute("magic").as_int();
	lrrhstats.speed = statsnode.child("lrrh").attribute("speed").as_int();
	lrrhstats.movement = statsnode.child("lrrh").attribute("movement").as_int();
	lrrhstats.attack = statsnode.child("lrrh").attribute("attack").as_int();
	lrrhstats.AttArea = statsnode.child("lrrh").attribute("AttArea").as_int();
	lrrhstats.Ab1Power = statsnode.child("lrrh").attribute("Ab1Power").as_int();
	lrrhstats.Ab2Power = statsnode.child("lrrh").attribute("Ab2Power").as_int();
	lrrhstats.Ab1Area = statsnode.child("lrrh").attribute("Ab1Area").as_int();
	lrrhstats.Ab2Area = statsnode.child("lrrh").attribute("Ab2Area").as_int();
	lrrhstats.healingpower = statsnode.child("lrrh").attribute("healingpower").as_int();

	lilpigstats.defense = statsnode.child("littlePig").attribute("defense").as_int();
	lilpigstats.magic = statsnode.child("littlePig").attribute("magic").as_int();
	lilpigstats.speed = statsnode.child("littlePig").attribute("speed").as_int();
	lilpigstats.movement = statsnode.child("littlePig").attribute("movement").as_int();
	lilpigstats.attack = statsnode.child("littlePig").attribute("attack").as_int();
	lilpigstats.AttArea = statsnode.child("littlePig").attribute("AttArea").as_int();
	lilpigstats.Ab1Power = statsnode.child("littlePig").attribute("Ab1Power").as_int();
	lilpigstats.Ab2Power = statsnode.child("littlePig").attribute("Ab2Power").as_int();
	lilpigstats.Ab1Area = statsnode.child("littlePig").attribute("Ab1Area").as_int();
	lilpigstats.Ab2Area = statsnode.child("littlePig").attribute("Ab2Area").as_int();
	lilpigstats.healingpower = statsnode.child("littlePig").attribute("healingpower").as_int();

	midpigstats.defense = statsnode.child("middlePig").attribute("defense").as_int();
	midpigstats.magic = statsnode.child("middlePig").attribute("magic").as_int();
	midpigstats.speed = statsnode.child("middlePig").attribute("speed").as_int();
	midpigstats.movement = statsnode.child("middlePig").attribute("movement").as_int();
	midpigstats.attack = statsnode.child("middlePig").attribute("attack").as_int();
	midpigstats.AttArea = statsnode.child("middlePig").attribute("AttArea").as_int();
	midpigstats.Ab1Power = statsnode.child("middlePig").attribute("Ab1Power").as_int();
	midpigstats.Ab2Power = statsnode.child("middlePig").attribute("Ab2Power").as_int();
	midpigstats.Ab1Area = statsnode.child("middlePig").attribute("Ab1Area").as_int();
	midpigstats.Ab2Area = statsnode.child("middlePig").attribute("Ab2Area").as_int();
	midpigstats.healingpower = statsnode.child("middlePig").attribute("healingpower").as_int();

	peterstats.defense = statsnode.child("peter").attribute("defense").as_int();
	peterstats.magic = statsnode.child("peter").attribute("magic").as_int();
	peterstats.speed = statsnode.child("peter").attribute("speed").as_int();
	peterstats.movement = statsnode.child("peter").attribute("movement").as_int();
	peterstats.attack = statsnode.child("peter").attribute("attack").as_int();
	peterstats.AttArea = statsnode.child("peter").attribute("AttArea").as_int();
	peterstats.Ab1Power = statsnode.child("peter").attribute("Ab1Power").as_int();
	peterstats.Ab2Power = statsnode.child("peter").attribute("Ab2Power").as_int();
	peterstats.Ab1Area = statsnode.child("peter").attribute("Ab1Area").as_int();
	peterstats.Ab2Area = statsnode.child("peter").attribute("Ab2Area").as_int();
	peterstats.healingpower = statsnode.child("peter").attribute("healingpower").as_int();

	addallstats();

	//Load inventory
	inventory.Clear();
	equipment.Clear();
	yoyo.ininventory = data.child("inventory").child("yoyo").attribute("isobtained").as_bool();
	yoyo.character = data.child("inventory").child("yoyo").attribute("character").as_int();
	if (yoyo.ininventory == true) {
		inventory.Add(yoyo);
		if (yoyo.character != 0) {
			equipment.Add(yoyo);
		}
	}
	handsxd.ininventory = data.child("inventory").child("handsxd").attribute("isobtained").as_bool();
	handsxd.character = data.child("inventory").child("handsxd").attribute("character").as_int();
	if (handsxd.ininventory == true) {
		inventory.Add(handsxd);
		if (handsxd.character != 0) {
			equipment.Add(handsxd);
		}
	}
	bow.ininventory = data.child("inventory").child("bow").attribute("isobtained").as_bool();
	bow.character = data.child("inventory").child("bow").attribute("character").as_int();
	if (bow.ininventory == true) {
		inventory.Add(bow);
		if (bow.character != 0) {
			equipment.Add(bow);
		}
	}
	club.ininventory = data.child("inventory").child("club").attribute("isobtained").as_bool();
	club.character = data.child("inventory").child("club").attribute("character").as_int();
	if (club.ininventory == true) {
		inventory.Add(club);
		if (club.character != 0) {
			equipment.Add(club);
		}
	}
	//Apply equipped item stats
	for (int i = 0; i < equipment.Count(); i++) {

		switch (equipment.At(i)->data.character)
		{
		case 1:
			additemstats(timmy, i);
			break;
		case 2:
			additemstats(bunny, i);
			break;
		case 3:
			additemstats(lrrh, i);
			break;
		case 4:
			additemstats(littlepig, i);
			break;
		case 5:
			additemstats(middlepig, i);
			break;
		case 6:
			additemstats(peter, i);
			break;
		}
		
	}

	return true;
}

bool TeamManager::SaveState(pugi::xml_node& data)
{
	//Save unlocked characters
	pugi::xml_node playable = data.append_child("playable");
	playable.append_attribute("istimmyplayable") = istimmyplayable;
	playable.append_attribute("isbunnyplayable") = isbunnyplayable;
	playable.append_attribute("islrrhplayable") = islrrhplayable;
	playable.append_attribute("islilpigplayable") = islilpigplayable;
	playable.append_attribute("ismidpigplayable") = ismidpigplayable;
	playable.append_attribute("ispeterplayable") = ispeterplayable;

	//Save characters in team
	pugi::xml_node onteam = data.append_child("onteam");
	onteam.append_attribute("IsTimmyOnTeam") = IsTimmyOnTeam;
	onteam.append_attribute("IsBunnyOnTeam") = IsBunnyOnTeam;
	onteam.append_attribute("IsLrrhOnTeam") = IsLrrhOnTeam;
	onteam.append_attribute("IsLilPigOnTeam") = IsLilPigOnTeam;
	onteam.append_attribute("IsMidPigOnTeam") = IsMidPigOnTeam;
	onteam.append_attribute("IsPeterOnTeam") = IsPeterOnTeam;

	//Save item
	pugi::xml_node inventory = data.append_child("inventory");
	inventory.append_child("yoyo");
	inventory.child("yoyo").append_attribute("isobtained") = yoyo.ininventory;
	inventory.child("yoyo").append_attribute("character") = yoyo.character;

	inventory.append_child("handsxd");
	inventory.child("handsxd").append_attribute("isobtained") = handsxd.ininventory;
	inventory.child("handsxd").append_attribute("character") = handsxd.character;

	inventory.append_child("bow");
	inventory.child("bow").append_attribute("isobtained") = bow.ininventory;
	inventory.child("bow").append_attribute("character") = bow.character;

	inventory.append_child("club");
	inventory.child("club").append_attribute("isobtained") = club.ininventory;
	inventory.child("club").append_attribute("character") = club.character;

	pugi::xml_node statsnode = data.append_child("stats");
	statsnode.append_child("timmy");
	statsnode.child("timmy").append_attribute("defense") = timmystats.defense;
	statsnode.child("timmy").append_attribute("magic") = timmystats.magic;
	statsnode.child("timmy").append_attribute("speed") = timmystats.speed;
	statsnode.child("timmy").append_attribute("movement") = timmystats.movement;
	statsnode.child("timmy").append_attribute("attack") = timmystats.attack;
	statsnode.child("timmy").append_attribute("AttArea") = timmystats.AttArea;
	statsnode.child("timmy").append_attribute("Ab1Power") = timmystats.Ab1Power;
	statsnode.child("timmy").append_attribute("Ab2Power") = timmystats.Ab2Power;
	statsnode.child("timmy").append_attribute("Ab1Area") = timmystats.Ab1Area;
	statsnode.child("timmy").append_attribute("Ab2Area") = timmystats.Ab2Area;
	statsnode.child("timmy").append_attribute("healingpower") = timmystats.healingpower;

	statsnode.append_child("bunny");
	statsnode.child("bunny").append_attribute("defense") = bunnystats.defense;
	statsnode.child("bunny").append_attribute("magic") = bunnystats.magic;
	statsnode.child("bunny").append_attribute("speed") = bunnystats.speed;
	statsnode.child("bunny").append_attribute("movement") = bunnystats.movement;
	statsnode.child("bunny").append_attribute("attack") = bunnystats.attack;
	statsnode.child("bunny").append_attribute("AttArea") = bunnystats.AttArea;
	statsnode.child("bunny").append_attribute("Ab1Power") = bunnystats.Ab1Power;
	statsnode.child("bunny").append_attribute("Ab2Power") = bunnystats.Ab2Power;
	statsnode.child("bunny").append_attribute("Ab1Area") = bunnystats.Ab1Area;
	statsnode.child("bunny").append_attribute("Ab2Area") = bunnystats.Ab2Area;
	statsnode.child("bunny").append_attribute("healingpower") = bunnystats.healingpower;

	statsnode.append_child("lrrh");
	statsnode.child("lrrh").append_attribute("defense") = lrrhstats.defense;
	statsnode.child("lrrh").append_attribute("magic") = lrrhstats.magic;
	statsnode.child("lrrh").append_attribute("speed") = lrrhstats.speed;
	statsnode.child("lrrh").append_attribute("movement") = lrrhstats.movement;
	statsnode.child("lrrh").append_attribute("attack") = lrrhstats.attack;
	statsnode.child("lrrh").append_attribute("AttArea") = lrrhstats.AttArea;
	statsnode.child("lrrh").append_attribute("Ab1Power") = lrrhstats.Ab1Power;
	statsnode.child("lrrh").append_attribute("Ab2Power") = lrrhstats.Ab2Power;
	statsnode.child("lrrh").append_attribute("Ab1Area") = lrrhstats.Ab1Area;
	statsnode.child("lrrh").append_attribute("Ab2Area") = lrrhstats.Ab2Area;
	statsnode.child("lrrh").append_attribute("healingpower") = lrrhstats.healingpower;

	statsnode.append_child("littlePig");
	statsnode.child("littlePig").append_attribute("defense") = lilpigstats.defense;
	statsnode.child("littlePig").append_attribute("magic") = lilpigstats.magic;
	statsnode.child("littlePig").append_attribute("speed") = lilpigstats.speed;
	statsnode.child("littlePig").append_attribute("movement") = lilpigstats.movement;
	statsnode.child("littlePig").append_attribute("attack") = lilpigstats.attack;
	statsnode.child("littlePig").append_attribute("AttArea") = lilpigstats.AttArea;
	statsnode.child("littlePig").append_attribute("Ab1Power") = lilpigstats.Ab1Power;
	statsnode.child("littlePig").append_attribute("Ab2Power") = lilpigstats.Ab2Power;
	statsnode.child("littlePig").append_attribute("Ab1Area") = lilpigstats.Ab1Area;
	statsnode.child("littlePig").append_attribute("Ab2Area") = lilpigstats.Ab2Area;
	statsnode.child("littlePig").append_attribute("healingpower") = lilpigstats.healingpower;

	statsnode.append_child("middlePig");
	statsnode.child("middlePig").append_attribute("defense") = midpigstats.defense;
	statsnode.child("middlePig").append_attribute("magic") = midpigstats.magic;
	statsnode.child("middlePig").append_attribute("speed") = midpigstats.speed;
	statsnode.child("middlePig").append_attribute("movement") = midpigstats.movement;
	statsnode.child("middlePig").append_attribute("attack") = midpigstats.attack;
	statsnode.child("middlePig").append_attribute("AttArea") = midpigstats.AttArea;
	statsnode.child("middlePig").append_attribute("Ab1Power") = midpigstats.Ab1Power;
	statsnode.child("middlePig").append_attribute("Ab2Power") = midpigstats.Ab2Power;
	statsnode.child("middlePig").append_attribute("Ab1Area") = midpigstats.Ab1Area;
	statsnode.child("middlePig").append_attribute("Ab2Area") = midpigstats.Ab2Area;
	statsnode.child("middlePig").append_attribute("healingpower") = midpigstats.healingpower;

	statsnode.append_child("peter");
	statsnode.child("peter").append_attribute("defense") = peterstats.defense;
	statsnode.child("peter").append_attribute("magic") = peterstats.magic;
	statsnode.child("peter").append_attribute("speed") = peterstats.speed;
	statsnode.child("peter").append_attribute("movement") = peterstats.movement;
	statsnode.child("peter").append_attribute("attack") = peterstats.attack;
	statsnode.child("peter").append_attribute("AttArea") = peterstats.AttArea;
	statsnode.child("peter").append_attribute("Ab1Power") = peterstats.Ab1Power;
	statsnode.child("peter").append_attribute("Ab2Power") = peterstats.Ab2Power;
	statsnode.child("peter").append_attribute("Ab1Area") = peterstats.Ab1Area;
	statsnode.child("peter").append_attribute("Ab2Area") = peterstats.Ab2Area;
	statsnode.child("peter").append_attribute("healingpower") = peterstats.healingpower;

	app->LoadGameRequest();

	return true;
}

bool TeamManager::additemstats(Entity* ent, int i)
{

	ent->defense += equipment.At(i)->data.defense;
	ent->magic += equipment.At(i)->data.magic;
	ent->speed += equipment.At(i)->data.speed;
	ent->movement += equipment.At(i)->data.movement;
	ent->attack += equipment.At(i)->data.attack;
	ent->AttArea += equipment.At(i)->data.AttArea;
	ent->Ab1Power += equipment.At(i)->data.Ab1Power;
	ent->Ab2Power += equipment.At(i)->data.Ab2Power;
	ent->Ab1Area += equipment.At(i)->data.Ab1Area;
	ent->Ab2Area += equipment.At(i)->data.Ab2Area;
	ent->healingpower += equipment.At(i)->data.healingpower;

	return false;
}

bool TeamManager::addallstats()
{
	
	for (int i = 0; i < characters.Count(); i++) {
		statsdone = false;
		characters.At(i)->data->Awake();
	}
	for (int j = 0; j < statslist.Count(); j++) {

		if (statslist.At(j)->data->character == 1) {
			timmy->defense += statslist.At(j)->data->defense;
			timmy->magic += statslist.At(j)->data->magic;
			timmy->speed += statslist.At(j)->data->speed;
			timmy->movement += statslist.At(j)->data->movement;
			timmy->attack += statslist.At(j)->data->attack;
			timmy->AttArea += statslist.At(j)->data->AttArea;
			timmy->Ab1Power += statslist.At(j)->data->Ab1Power;
			timmy->Ab2Power += statslist.At(j)->data->Ab2Power;
			timmy->Ab1Area += statslist.At(j)->data->Ab1Area;
			timmy->Ab2Area += statslist.At(j)->data->Ab2Area;
			timmy->healingpower += statslist.At(j)->data->healingpower;
		}
		if (statslist.At(j)->data->character == 2) {
			bunny->defense += statslist.At(j)->data->defense;
			bunny->magic += statslist.At(j)->data->magic;
			bunny->speed += statslist.At(j)->data->speed;
			bunny->movement += statslist.At(j)->data->movement;
			bunny->attack += statslist.At(j)->data->attack;
			bunny->AttArea += statslist.At(j)->data->AttArea;
			bunny->Ab1Power += statslist.At(j)->data->Ab1Power;
			bunny->Ab2Power += statslist.At(j)->data->Ab2Power;
			bunny->Ab1Area += statslist.At(j)->data->Ab1Area;
			bunny->Ab2Area += statslist.At(j)->data->Ab2Area;
			bunny->healingpower += statslist.At(j)->data->healingpower;
		}
		if (statslist.At(j)->data->character == 3 && islrrhplayable == true) {
			lrrh->defense += statslist.At(j)->data->defense;
			lrrh->magic += statslist.At(j)->data->magic;
			lrrh->speed += statslist.At(j)->data->speed;
			lrrh->movement += statslist.At(j)->data->movement;
			lrrh->attack += statslist.At(j)->data->attack;
			lrrh->AttArea += statslist.At(j)->data->AttArea;
			lrrh->Ab1Power += statslist.At(j)->data->Ab1Power;
			lrrh->Ab2Power += statslist.At(j)->data->Ab2Power;
			lrrh->Ab1Area += statslist.At(j)->data->Ab1Area;
			lrrh->Ab2Area += statslist.At(j)->data->Ab2Area;
			lrrh->healingpower += statslist.At(j)->data->healingpower;
		}
		if (statslist.At(j)->data->character == 4 && islilpigplayable == true) {
			littlepig->defense += statslist.At(j)->data->defense;
			littlepig->magic += statslist.At(j)->data->magic;
			littlepig->speed += statslist.At(j)->data->speed;
			littlepig->movement += statslist.At(j)->data->movement;
			littlepig->attack += statslist.At(j)->data->attack;
			littlepig->AttArea += statslist.At(j)->data->AttArea;
			littlepig->Ab1Power += statslist.At(j)->data->Ab1Power;
			littlepig->Ab2Power += statslist.At(j)->data->Ab2Power;
			littlepig->Ab1Area += statslist.At(j)->data->Ab1Area;
			littlepig->Ab2Area += statslist.At(j)->data->Ab2Area;
			littlepig->healingpower += statslist.At(j)->data->healingpower;
		}
		if (statslist.At(j)->data->character == 5 && ismidpigplayable == true) {
			middlepig->defense += statslist.At(j)->data->defense;
			middlepig->magic += statslist.At(j)->data->magic;
			middlepig->speed += statslist.At(j)->data->speed;
			middlepig->movement += statslist.At(j)->data->movement;
			middlepig->attack += statslist.At(j)->data->attack;
			middlepig->AttArea += statslist.At(j)->data->AttArea;
			middlepig->Ab1Power += statslist.At(j)->data->Ab1Power;
			middlepig->Ab2Power += statslist.At(j)->data->Ab2Power;
			middlepig->Ab1Area += statslist.At(j)->data->Ab1Area;
			middlepig->Ab2Area += statslist.At(j)->data->Ab2Area;
			middlepig->healingpower += statslist.At(j)->data->healingpower;
		}
		if (statslist.At(j)->data->character == 6 && ispeterplayable == true) {
			peter->defense += statslist.At(j)->data->defense;
			peter->magic += statslist.At(j)->data->magic;
			peter->speed += statslist.At(j)->data->speed;
			peter->movement += statslist.At(j)->data->movement;
			peter->attack += statslist.At(j)->data->attack;
			peter->AttArea += statslist.At(j)->data->AttArea;
			peter->Ab1Power += statslist.At(j)->data->Ab1Power;
			peter->Ab2Power += statslist.At(j)->data->Ab2Power;
			peter->Ab1Area += statslist.At(j)->data->Ab1Area;
			peter->Ab2Area += statslist.At(j)->data->Ab2Area;
			peter->healingpower += statslist.At(j)->data->healingpower;
		}
	}

	

	return false;
}
