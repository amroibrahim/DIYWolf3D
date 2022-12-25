#include "SettingsGUI.h"

SettingsGUI::SettingsGUI(Configuration* configuration, Player* player) : show_log_window_(false), configuration_(configuration), player_(player)
{

}

void SettingsGUI::Initialize(SDL_Window* window, SDL_Renderer* renderer)
{
	show_log_window_ = false;

	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	sky_color_ = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	floor_color_ = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	counter = 0;
}

void SettingsGUI::ProcessEvent(SDL_Event* event)
{
	ImGui_ImplSDL2_ProcessEvent(event);
}

void SettingsGUI::Update()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void SettingsGUI::Render()
{
	// Generate the windows to render
	BuildWindows();

	// Rendering
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void SettingsGUI::BuildWindows()
{
	MainSettingsWindow();

	if (show_log_window_)
	{
		configuration_->log.Render("Logs");
	}
}

void SettingsGUI::MainSettingsWindow()
{
	ImGui::Begin("Settings");
	ImGui::Text("Display settings");
	ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Player position (%.3f,%.3f), Angle = %.3f, tan = %.3f", player_->x, player_->y, player_->rotation_angle, tan(player_->rotation_angle));
	ImGui::SliderFloat("Framerate Limiter", &configuration_->display.framerate, 1.0f, 244.0f);
	ImGui::SliderFloat("Mini map scale", &configuration_->map.mini_map_magnification_scale, 0.0f, 1.0f);
	ImGui::SliderFloat("Mini map transparency", &configuration_->map.transparency, 0.0f, 1.0f);
	ImGui::Checkbox("Mini map", &configuration_->game.mini_map_enabled);
	ImGui::Checkbox("Logs Window", &show_log_window_);
	ImGui::ColorEdit3("Sky color", (float*)&sky_color_);
	ImGui::ColorEdit3("Floor color", (float*)&floor_color_);

	configuration_->render.sky_color_r = sky_color_.x * 255;
	configuration_->render.sky_color_g = sky_color_.y * 255;
	configuration_->render.sky_color_b = sky_color_.z * 255;

	configuration_->render.floor_color_r = floor_color_.x * 255;
	configuration_->render.floor_color_g = floor_color_.y * 255;
	configuration_->render.floor_color_b = floor_color_.z * 255;

	ImGui::End();
}

void SettingsGUI::Clean()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
