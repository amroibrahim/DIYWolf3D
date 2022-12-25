#pragma once

#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include "Configuration.h"
#include "Player.h"

class SettingsGUI
{
public:
	SettingsGUI(Configuration* configuration, Player* player_);
	void Initialize(SDL_Window* window, SDL_Renderer* renderer);
	void ProcessEvent(SDL_Event* event);
	void Update();
	void Render();
	void Clean();

protected:
	void BuildWindows();
	void MainSettingsWindow();

	bool show_log_window_;
	Configuration* configuration_;
	Player* player_;
	// Settings windows variables
	ImVec4 sky_color_;
	ImVec4 floor_color_;

	int counter;
};

