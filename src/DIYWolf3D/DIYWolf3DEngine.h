#pragma once

#include <SDL.h>
#include "SettingsGUI.h"
#include "MiniMap.h"
#include "Player.h"
#include "RayCastManager.h"
#include "TextureManager.h"

class DIYWolf3DEngine
{
public:
	DIYWolf3DEngine();
	void Initialize();

	virtual ~DIYWolf3DEngine();

	void ProcessInput();
	void Render();
	void Update();
	void Delay();
	void Quit();
	void Clean();

	bool IsOver();

protected:
	void KeyPress(const Uint8* key_states);
	SDL_Surface* CreateSurfaceBuffer(int width, int hight);

	SDL_Window* window_;
	SDL_Renderer* renderer_;
	SDL_Surface* main_surface_;
	Configuration configuration_;
	SettingsGUI settings_gui_;
	Level level_;
	Player player_;
	MiniMap mini_map_;
	RayCastManager ray_caster_;
	TextureManager texture_manager_;

	uint32_t frame_length_;
	uint32_t last_frame_time_;

	int screen_width_;
	int screen_height_;
	bool is_over_;

};
