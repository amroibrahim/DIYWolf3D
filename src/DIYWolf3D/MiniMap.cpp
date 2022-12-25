#include "MiniMap.h"
#include "SDL_Draw/SDL_Draw.h"

MiniMap::MiniMap(Configuration* configuration, Player* player, Level* level, RayCastManager* ray_cast) : GameObject(configuration), player_(player), level_(level), mini_map_surface_(nullptr), ray_cast_(ray_cast)
{

}

void MiniMap::Initialize()
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	width_ = level_->tile_size * level_->map_colomns;
	height_ = level_->tile_size * level_->map_raw;
	mini_map_surface_ = SDL_CreateRGBSurface(0, width_, height_, 32, rmask, gmask, bmask, amask);
}

void MiniMap::Update(float elapsed_time)
{
}

void MiniMap::Render()
{
	DrawGrid();
	DrawRays();
	DrawPLayer();
	SDL_Texture* mini_map_texture = SDL_CreateTextureFromSurface(configuration_->render.renderer, mini_map_surface_);
	SDL_Rect dest = { 0, 0,
		width_ * configuration_->map.mini_map_magnification_scale,
		height_ * configuration_->map.mini_map_magnification_scale };

	SDL_SetRenderDrawBlendMode(configuration_->render.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(mini_map_texture, configuration_->map.transparency * 255);
	//SDL_SetRenderDrawColor(configuration_->render.renderer, 255, 255, 255, 100);
	SDL_RenderCopy(configuration_->render.renderer, mini_map_texture, NULL, &dest);
	SDL_DestroyTexture(mini_map_texture);
}

void MiniMap::Clean()
{
	SDL_FreeSurface(mini_map_surface_);
	mini_map_surface_ = nullptr;
}

void MiniMap::DrawGrid()
{
	float scale = level_->tile_size; // *configuration_->map.mini_map_magnification_scale;


	// AngryCPPCoder: to fix gaps in tiles alignment 
	//int x_pos = 0;
	//int y_pos = 0;

	SDL_Color color;

	for (int y = 0; y < level_->map_raw; ++y)
	{
		//x_pos = 0;
		for (int x = 0; x < level_->map_colomns; ++x)
		{

			if (level_->level[y][x] == 0)
			{
				color.r = configuration_->map.empty_cell_color_r;
				color.g = configuration_->map.empty_cell_color_g;
				color.b = configuration_->map.empty_cell_color_b;
			}
			else
			{
				color.r = configuration_->map.wall_cell_color_r;
				color.g = configuration_->map.wall_cell_color_g;
				color.b = configuration_->map.wall_cell_color_b;
			}

			SDL_Rect tile =
			{
				x * scale, //x_pos, // x * scale
				y * scale, //y_pos, // y * scale
				(int)scale,
				(int)scale
			};

			SDL_FillRect(mini_map_surface_, &tile, SDL_MapRGB(mini_map_surface_->format, color.r, color.g, color.b));
			//return;
		}
		//y_pos += (int) scale;

	}

	for (int y = 0; y < level_->map_raw; ++y)
	{
		SDL_DrawLine(mini_map_surface_, 0, y * scale, mini_map_surface_->w, y * scale, 0xFF0000FF);
		for (int x = 0; x < level_->map_colomns; ++x)
		{
			SDL_DrawLine(mini_map_surface_, x * scale, 0, x * scale, mini_map_surface_->h, 0xFF0000FF);
		}
	}
}

void MiniMap::DrawPLayer()
{
	SDL_Rect tile = {
		player_->x - 10,
		player_->y - 10,
		20,
		20 };

	SDL_FillRect(mini_map_surface_, &tile, SDL_MapRGB(mini_map_surface_->format, 255, 0, 0));

	SDL_DrawLine(mini_map_surface_, player_->x,
		player_->y,
		player_->x + cos(player_->rotation_angle) * 50 * configuration_->map.mini_map_magnification_scale,
		player_->y + sin(player_->rotation_angle) * 50 * configuration_->map.mini_map_magnification_scale,
		SDL_MapRGB(mini_map_surface_->format, 255, 0, 0));
}

void MiniMap::DrawRays()
{
	ray_cast_->RenderMiniMap(mini_map_surface_);
}
