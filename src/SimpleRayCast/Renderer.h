#pragma once

#include <SDL.h>

#include "Angle.h"
#include "Player.h"
#include "Map.h"

class Renderer
{
public:
    Renderer(int iScreenWidth, int iScreenHight);
    ~Renderer();
    void RenderView(SDL_Renderer *pRenderer);

    bool Init(Player *pPlayer, Map *pMap);

protected:
    void DrawBackGround(SDL_Renderer *pRenderer);
    void DrawWorld(SDL_Renderer *pRenderer);
    void DrawWallAt(SDL_Renderer *pRenderer, int iRow, int iHight);

    float RayCastAtAngle(Angle& CastAngle);
    float RayCastOnYSteps(Angle& CastAngle);
    float RayCastOnXSteps(Angle& CastAngle);

    int m_iScreenWidth;
    int m_iScreenHight;
    Player *m_pPlayer;
    Map *m_pMap;
};

