#include "Ray.h"

#include <cmath>
#include <SDL_stdinc.h>

Ray::Ray(Level* level) : level_(level)
{
}

void Ray::Setup(float x_origin, float y_origin, float angle)
{
	x_origin_ = x_origin;
	y_origin_ = y_origin;

	angle_ = std::fmod(angle, M_PI * 2);

	if (angle_ < 0)
	{
		angle_ = angle_ + (M_PI * 2);
	}

	// *--------------------------> X+
	// |                  1.5 PI
	// |
	// |                   Up (N)
	// |
	// |  PI    Left (W)  (Player)  Right (E)    0
	// | 
	// |                  Down (S)
	// | 
	// |                  0.5 PI
	// V 
	// 
	// y+

	// Update Ray direction
	direction_ = DIRECTION::UNKNOWN;

	if (0 < angle_ && angle_ < M_PI)
	{
		direction_ |= DIRECTION::DOWN;
	}
	else
	{
		direction_ |= DIRECTION::UP;
	}

	if (0.5 * M_PI < angle_ && angle_ < 1.5 * M_PI)
	{
		direction_ |= DIRECTION::LEFT;
	}
	else
	{
		direction_ |= DIRECTION::RIGHT;
	}
}

void Ray::Cast()
{
	float x_hit_horizontal = 0;
	float y_hit_horizontal = 0;
	float x_hit_vertical = 0;
	float y_hit_vertical = 0;
	int horizontal_cell_id = 0;
	int vertical_cell_id = 0;

	float horizontal_length = HorizontalCast(x_hit_horizontal, y_hit_horizontal, horizontal_cell_id);
	float vertical_length = VerticalCast(x_hit_vertical, y_hit_vertical, vertical_cell_id);

	if (vertical_length < horizontal_length)
	{
		is_vertical_hit = true;
		distance_ = vertical_length;
		x_hit_ = x_hit_vertical;
		y_hit_ = y_hit_vertical;
		cell_id_ = vertical_cell_id;
	}
	else
	{
		is_vertical_hit = false;
		distance_ = horizontal_length;
		x_hit_ = x_hit_horizontal;
		y_hit_ = y_hit_horizontal;
		cell_id_ = horizontal_cell_id;
	}
}

float Ray::HorizontalCast(float& x_hit, float& y_hit, int& cell_id)
{
	// TODO: fix: tan can be 0
	float angle_tan = tan(angle_);

	float y_intercept = level_->GetYCellBorder(y_origin_) + ((direction_ & DIRECTION::DOWN) ? level_->GetTileSize() : 0);
	float x_intercept = x_origin_ + (y_intercept - y_origin_) / angle_tan;

	float y_step = level_->GetTileSize() * ((direction_ & DIRECTION::UP) ? -1 : 1);
	float x_step = level_->GetTileSize() / angle_tan;

	x_step *= ((direction_ & DIRECTION::LEFT) && x_step > 0) ? -1 : 1;
	x_step *= ((direction_ & DIRECTION::RIGHT) && x_step < 0) ? -1 : 1;

	float x_next = x_intercept;
	float y_next = y_intercept;

	while (!level_->IsWall(x_next, y_next + ((direction_ & DIRECTION::UP) ? -1 : 0)))
	{
		x_next += x_step;
		y_next += y_step;
	}

	cell_id = level_->IsWall(x_next, y_next + ((direction_ & DIRECTION::UP) ? -1 : 0));
	x_hit = x_next;
	y_hit = y_next;

	return Length(x_origin_, y_origin_, x_hit, y_hit);
}

float Ray::VerticalCast(float& x_hit, float& y_hit, int& cell_id)
{
	float angle_tan = tan((angle_) ? angle_ : 0.001);

	float x_intercept = level_->GetYCellBorder(x_origin_) + ((direction_ & DIRECTION::RIGHT) ? level_->GetTileSize() : 0);
	float y_intercept = y_origin_ + (x_intercept - x_origin_) * angle_tan;

	float x_step = level_->GetTileSize() * ((direction_ & DIRECTION::LEFT) ? -1 : 1);
	float y_step = level_->GetTileSize() * angle_tan;

	y_step *= ((direction_ & DIRECTION::UP) && y_step > 0) ? -1 : 1;
	y_step *= ((direction_ & DIRECTION::DOWN) && y_step < 0) ? -1 : 1;

	float x_next = x_intercept;
	float y_next = y_intercept;
	while (!level_->IsWall(x_next + ((direction_ & DIRECTION::LEFT) ? -1 : 0), y_next))
	{
		x_next += x_step;
		y_next += y_step;
	}

	cell_id = level_->IsWall(x_next + ((direction_ & DIRECTION::LEFT) ? -1 : 0), y_next);
	x_hit = x_next;
	y_hit = y_next;

	return Length(x_origin_, y_origin_, x_hit, y_hit);
}

float Ray::Length(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}