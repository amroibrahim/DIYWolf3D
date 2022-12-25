// SDL Draw

#ifndef SDL_DRAW_H
#define SDL_DRAW_H

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

enum SDL_DRAW_LINE_ALGORITHM
{
	DDA,
	BRESENHAM
};

void SDL_DrawLine(SDL_Surface* surface, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Uint32 color);

/**
 * Draw line to a SDL surface using digital differential analyzer algorithm.
 *
 * The x and y point coordinates should be uint32_t.
 * line point outside the surface will be ignored.
 * 
 * \param surface point to the surface to be draw the line
 * \param x1, y1 starting point coordinates
 * \param x2, y2 end point coordinates
 *
 */
void SDL_DrawLine_DDA(SDL_Surface* surface, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Uint32 color);

/**
 * Draw line to a SDL surface using Bresenham algorithm.
 * Based on https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm
 * 
 * The x and y point coordinates should be uint32_t.
 * line point outside the surface will be ignored.
 *
 * \param surface point to the surface to be draw the line
 * \param x1, y1 starting point coordinates
 * \param x2, y2 end point coordinates
 *
 */
void SDL_DrawLine_Bresenham(SDL_Surface* surface, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Uint32 color);

#ifdef __cplusplus
} //extern "C" 
#endif

#endif  // SDL_DRAW_H
