#pragma once
#include "GameObject.h"
#include "Level.h"
#include "Player.h"
#include "RayCastManager.h"

class MiniMap : GameObject
{
public:
	MiniMap(Configuration* configuration, Player* player, Level* level, RayCastManager* ray_cast);

	void Initialize() override;;
	void Update(float elapsed_time) override;
	void Render() override;
	void Clean() override;

protected:
	void DrawGrid();
	int width_;
	int height_;
	Level* level_;
	Player* player_;
	RayCastManager* ray_cast_;
	SDL_Surface* mini_map_surface_;

private:
	void DrawPLayer();
	void DrawRays();
};

