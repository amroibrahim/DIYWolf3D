#include "Player.h"

#include <SDL_stdinc.h>

Player::Player(Configuration* configuration, Level* level) : GameObject(configuration), radius(configuration->map.mini_map_player_size), rotation_direction(0), move_direction(0), move_speed(0), level_(level)
{
	rotation_angle = 0;
	rotation_speed = 2 * (M_PI / 180);
	fov_ = 60 * (M_PI / 180);
	move_speed = 0.6;
	x = level_->player_start_x;
	y = level_->player_start_y;;
}

void Player::Initialize()
{
}

void Player::Update(float elapsed_time)
{
	rotation_angle += rotation_speed * rotation_direction;
	int move_step = move_direction * move_speed * elapsed_time;
	if (move_step != 0)
	{
		configuration_->log.Log("Move Steps %d \n", move_step);
	}
	float next_x = x + move_step * cos(rotation_angle);
	float next_y = y + move_step * sin(rotation_angle);

	if (level_->IsWall(next_x, next_y) == 0)
	{
		x = next_x;
		y = next_y;
	}

	rotation_direction = 0;
	move_direction = 0;
}

void Player::Render()
{

}

void Player::Clean()
{
}
