#include "RayCastManager.h"
#include "TextureManager.h"
#include "SDL_Draw/SDL_Draw.h"

RayCastManager::RayCastManager(Configuration* configuration, TextureManager* texture_manager, Level* level, Player* player) : GameObject(configuration), ray_width_(1), level_(level), player_(player), texture_manager_(texture_manager)
{
}

void RayCastManager::Initialize()
{
	rays_.clear();
	Ray ray(level_);
	int cast_ray_count = configuration_->display.back_buffer_width / ray_width_;
	for (int i = 0; i < cast_ray_count; ++i)
	{
		// a new copy of ray will created for each push
		rays_.push_back(ray);
	}
}

void RayCastManager::Update(float elapsed_time)
{
	// get the start angle all way to the left
	float ray_angle = player_->rotation_angle - ((float)player_->fov_ / 2.0f);
	float angle_increments = (float)player_->fov_ / rays_.size();

	for (auto& ray : rays_)
	{
		ray.Setup(player_->x, player_->y, ray_angle);
		ray.Cast();
		ray_angle += angle_increments;
	}
}

void RayCastManager::Render()
{
	ProectRenderRays();

	SDL_Texture* surface_texture = SDL_CreateTextureFromSurface(configuration_->render.renderer, surface_);
	SDL_Rect dest = { 0, 0, surface_->w, surface_->h };
	SDL_RenderCopy(configuration_->render.renderer, surface_texture, NULL, NULL);
	SDL_DestroyTexture(surface_texture);
}

void RayCastManager::ProectRenderRays()
{
	Uint32 sky_color = SDL_MapRGB(surface_->format,
		configuration_->render.sky_color_r,
		configuration_->render.sky_color_g,
		configuration_->render.sky_color_b);

	Uint32 floor_color = SDL_MapRGB(surface_->format,
		configuration_->render.floor_color_r,
		configuration_->render.floor_color_g,
		configuration_->render.floor_color_b);

	Uint32* pixels = (Uint32*)surface_->pixels;

	for (int x = 0; x < rays_.size(); ++x)
	{
		auto& ray = rays_[x];
		ray.Cast();
		
		if (ray.distance_ - 0.001 < 0)
		{
			ray.distance_ = 0.001;
		}

		float distortion_correction_distance = ray.distance_ * cos(ray.angle_ - player_->rotation_angle);
		float wall_height = (level_->tile_size / distortion_correction_distance) * projection_plane_;

		int wall_start = (surface_->h / 2) - (wall_height / 2);
		int wall_end = (surface_->h / 2) + (wall_height / 2);

		DrawSky(x, wall_start, pixels, sky_color);
		DrawWall(x, wall_start, wall_end, ray, pixels);
		DrawFloor(x, wall_end, pixels, floor_color);
	}
}

void RayCastManager::DrawFloor(int x, int floor_start, Uint32* pixels, Uint32 floor_color)
{
	int end_pixel = floor_start > surface_->h ? surface_->h : floor_start;

	for (int y = end_pixel; y < surface_->h; y++)
	{
		pixels[(surface_->w * y) + x] = floor_color;
	}
}

void RayCastManager::DrawWall(int x, int wall_start, int wall_end, Ray& ray, Uint32* pixels)
{
	SDL_Surface* texture_surface = texture_manager_->getTextureBuffer(ray.cell_id_);

	Uint32* texture = (Uint32*)texture_surface->pixels;

	int texture_x_offset = 0;
	if (ray.is_vertical_hit)
	{
		texture_x_offset = ((int)ray.y_hit_ % level_->tile_size);
	}
	else
	{
		texture_x_offset = ((int)ray.x_hit_ % level_->tile_size);
	}

	int start_pixel = wall_start < 0 ? 0 : wall_start;
	int end_pixel = wall_end > surface_->h ? surface_->h : wall_end;

	for (int y = start_pixel; y < end_pixel; y++)
	{
		int y_start = y + ((wall_end - wall_start) / 2) - (surface_->h / 2);
		if (y_start < 0)
		{
			y_start = 0;
		}
		int texture_y_offset = y_start * ((float)texture_surface->h / (wall_end - wall_start));

		pixels[(surface_->w * y) + x] = texture[(texture_surface->w * texture_y_offset) + texture_x_offset];
	}
}

void RayCastManager::DrawSky(int x, int wall_start, Uint32* pixels, Uint32 sky_color)
{
	int end_pixel = wall_start < 0 ? 0 : wall_start;
	for (int y = 0; y < end_pixel; y++)
	{
		pixels[(surface_->w * y) + x] = sky_color;
	}
}

void RayCastManager::Clean()
{
}

void RayCastManager::SetSurface(SDL_Surface* surface)
{
	surface_ = surface;
	projection_plane_ = (surface_->w / 2) / tan(player_->fov_ / 2.0f);
}

void RayCastManager::RenderMiniMap(SDL_Surface* mini_map_surface)
{
	int i = 0;
	for (auto& ray : rays_)
	{
		SDL_DrawLine(mini_map_surface, ray.x_origin_,
			ray.y_origin_,
			ray.x_hit_,
			ray.y_hit_,
			SDL_MapRGB(mini_map_surface->format, 255, 0, 0));
	}
}
