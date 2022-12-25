#pragma once

#include "GameObject.h"
#include "Level.h"

class Player : public GameObject
{
public:
	Player(Configuration* configuration, Level* level);
	void Initialize() override;
	void Update(float elapsed_time) override;
	void Render() override;
	void Clean() override;

	//protected:
	float x;
	float y;
	float rotation_angle;
	float rotation_speed;
	float move_speed;
	int radius;
	int rotation_direction;
	int move_direction;
	int fov_;
	Level* level_;
};

