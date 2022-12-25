// SDL Draw

#include "SDL_Draw.h" 

#define ROUND(n) ((int) (n + 0.5))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

enum SDL_DRAW_LINE_ALGORITHM SDL_DRAW_LINE_ALGO = BRESENHAM;

void SDL_DrawLine(SDL_Surface* surface, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Uint32 color)
{
	//if (x1 < 0 || surface->w <= x1 || 
	//	x2 < 0 || surface->w <= x2 ||
	//	y1 < 0 || surface->h <= y1 ||
	//	y2 < 0 || surface->h <= y2)
	//{
	//	return;
	//}

	switch (SDL_DRAW_LINE_ALGO)
	{
	case DDA:
		SDL_DrawLine_DDA(surface, x1, y1, x2, y2, color);
		break;

	case BRESENHAM:
		SDL_DrawLine_Bresenham(surface, x1, y1, x2, y2, color);
		break;
	}
}

void SDL_DrawLine_DDA(SDL_Surface* surface, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Uint32 color)
{
	int x_delta = x2 - x1;
	int y_delta = y2 - y1;

	int steps = MAX(abs(x_delta), abs(y_delta));

	if (steps <= 0)
	{
		return;
	}

	float x_current = x1;
	float y_current = y1;

	float x_incremant = (float)x_delta / (float)steps;
	float y_incremant = (float)y_delta / (float)steps;

	Uint32* pixels = (Uint32*)surface->pixels;

	int step = 0;
	do
	{
		if (0 <= x_current && x_current < surface->w &&
			0 <= y_current && y_current < surface->h)
		{
			pixels[(ROUND(y_current) * surface->w) + ROUND(x_current)] = color;
		}

		x_current += x_incremant;
		y_current += y_incremant;
		++step;

	} while (step <= steps);
}

void SDL_DrawLine_Bresenham(SDL_Surface* surface, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Uint32 color)
{

	int x_delta = abs(x2 - x1);
	int y_delta = abs(y2 - y1);

	int x_incremant = x1 < x2 ? 1 : -1;
	int y_incremant = y1 < y2 ? 1 : -1;

	int x_current = x1;
	int y_current = y1;

	int err = (x_delta > y_delta ? x_delta : -y_delta) / 2;

	Uint32* pixels = (Uint32*)surface->pixels;

	pixels[(y_current * surface->w) + x_current] = color;

	while (x_current != x2 || y_current != y2)
	{
		int err_current = err;
		if (err_current > -x_delta)
		{
			err -= y_delta;
			x_current += x_incremant;
		}

		if (err_current < y_delta)
		{
			err += x_delta;
			y_current += y_incremant;
		}

		pixels[(y_current * surface->w) + x_current] = color;
	};
}
