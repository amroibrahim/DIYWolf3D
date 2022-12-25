#pragma once

#include <SDL.h>
#include <cstdint>

#include "LogGUI.h"

// Display settings
struct Display
{
	int screen_buffer_width = 640 * 2;
	int screen_buffer_height = 400 * 2;

	int back_buffer_width = 320;
	int back_buffer_hight = 200;

	float framerate = 60;

	SDL_Window* window;
};

// Render settings
struct Render
{
	uint8_t sky_color_r = 0;
	uint8_t sky_color_g = 0;
	uint8_t sky_color_b = 0;

	uint8_t floor_color_r = 0;
	uint8_t floor_color_g = 0;
	uint8_t floor_color_b = 0;

	SDL_Renderer* renderer;
};

// Game settings
struct Game
{
	bool mini_map_enabled = true;
};

struct Map
{
	float mini_map_magnification_scale = 0.2f;
	float transparency = 1.0f;

	int mini_map_player_size = 20;


	uint8_t wall_cell_color_r = 0;
	uint8_t wall_cell_color_g = 0;
	uint8_t wall_cell_color_b = 255;

	uint8_t empty_cell_color_r = 255;
	uint8_t empty_cell_color_g = 255;
	uint8_t empty_cell_color_b = 255;
};

struct Configuration
{
	Display display;
	Render render;
	Game game;
	Map map;
	LogGUI log;
};
