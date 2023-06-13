#include "GuiSlider.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Window.h"
#include "GuiManager.h"
#include "SDL_mixer/include/SDL_mixer.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, SDL_Texture* tex, const char* text) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->text = text;
	this->tex = tex;

	canClick = true;
	drawBasic = false;

	this->x1 = 0;
	this->y1 = 0;
	this->x2 = 0;
	this->y2 = 0;

	debug = false;

	buttonHovering = app->audio->LoadFx("Assets/Audio/Fx/HoveringButton.wav");
	hoverOnce = false;

}

GuiSlider::~GuiSlider()
{

}

bool GuiSlider::Update(float dt)
{

	if (state != GuiControlState::DISABLED)
	{
		int x0, y0;
		app->input->GetMousePosition(x0, y0);

		if (state == GuiControlState::FOCUSED) {

			app->input->GetMousePosition(x1, y1);

		}

		if (state == GuiControlState::PRESSED) {

			app->input->GetMousePosition(x2, y2);
		}

		if (x0 >= bounds.x && x0 <= bounds.x + bounds.w && y0 >= bounds.y && y0 <= bounds.y + bounds.h) {

			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT || app->input->pad->GetButton(SDL_CONTROLLER_BUTTON_X) == KEY_REPEAT) {

				state = GuiControlState::PRESSED;

				if (posx >= 0 && posx + bounds.w <= app->win->width) {

					if (bounds.x >= 1258 && bounds.x <= 1659) {

						bounds.x = x0 - bounds.w / 2;
						posx = x0 - bounds.w / 2;

					}
					else {

						if (bounds.x > 1659) {

							bounds.x = 1659;
							posx = 1659;

						}
						else {

							bounds.x = 1258;
							posx = 1258;

						}

					}

				}
			}

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP || app->input->pad->GetButton(SDL_CONTROLLER_BUTTON_X) == KEY_UP) {

				NotifyObserver();
			}
		}
		else {

			state = GuiControlState::NORMAL;
			if (posx < 0) {

				posx = 0;

			}
			if (posx + bounds.w > app->win->width) {

				posx = app->win->width;
			}

		}
	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{

	rect.x = 0;
	rect.y = 0;
	rect.w = bounds.w;
	rect.h = bounds.h;

	switch (state)
	{
	case GuiControlState::DISABLED:
		//app->render->DrawRectangle(bounds, 200, 200, 200, 255, true, false);
		break;
	case GuiControlState::NORMAL:

		app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);
		hoverOnce = false;

		break;
	case GuiControlState::FOCUSED:

		if (!hoverOnce) {
			app->audio->PlayFx(app->guiManager->hoverFxId);
			hoverOnce = true;
		}

		rect.y = bounds.h;
		app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);

		break;
	case GuiControlState::PRESSED:

		rect.y = bounds.h * 2;
		app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);

		break;
	default:
		break;
	}


	return false;
}