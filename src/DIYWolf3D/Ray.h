#pragma once

#include "Level.h"

namespace DIRECTION
{
	const char UNKNOWN = 0;
	const char UP = 1;
	const char DOWN = 2;
	const char LEFT = 4;
	const char RIGHT = 8;
};

class Ray
{
public:
	Ray(Level* level);
	void Setup(float x_origin, float y_origin, float angle);
	void Cast();

	//protected:
	float HorizontalCast(float& x_hit, float& y_hit, int& cell_id);
	float VerticalCast(float& x_hit, float& y_hit, int& cell_id);
	float Length(float x1, float y1, float x2, float y2);
	float x_origin_;
	float y_origin_;
	float angle_;
	float x_hit_;
	float y_hit_;
	float distance_;
	int cell_id_;
	char direction_;
	bool is_vertical_hit;

	Level* level_;
};

