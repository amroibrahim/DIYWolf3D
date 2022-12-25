#pragma once
#include <vector>

#include "GameObject.h"
#include "Ray.h"
#include "Player.h"
#include "Level.h"
#include "TextureManager.h"

class RayCastManager : public GameObject
{
public:
	RayCastManager(Configuration* configuration, TextureManager* texture_manager, Level* level, Player* player);
	void Initialize() override;
	void Update(float elapsed_time) override;
	void Render() override;
	void Clean() override;

	void SetSurface(SDL_Surface* surface);
	void RenderMiniMap(SDL_Surface* mini_map_surface);

protected:
	void ProectRenderRays();
	void DrawSky(int x, int sky_end, Uint32* pixels, Uint32 sky_color);
	void DrawWall(int x, int wall_start, int wall_end, Ray& ray, Uint32* pixels);
	void DrawFloor(int x, int floor_start, Uint32* pixels, Uint32 floor_color);

	std::vector<Ray> rays_;
	int ray_width_;
	float projection_plane_;
	Player* player_;
	Level* level_;
	SDL_Surface* surface_;
	TextureManager* texture_manager_;
};

