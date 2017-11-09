#include "Renderer.h"

#include "Angle.h"

#include <iostream>


Renderer::Renderer(int iScreenWidth, int iScreenHight)
{
	m_iScreenWidth = iScreenWidth;
	m_iScreenHight = iScreenHight;
}

Renderer::~Renderer()
{
}

bool Renderer::Init(Player *pPlayer, Map *pMap)
{
	if (pPlayer == nullptr || pMap == nullptr)
	{
		return false;
	}

	m_pPlayer = pPlayer;
	m_pMap = pMap;
	return true;
}

void Renderer::RenderView(SDL_Renderer *pRenderer)
{
	//Lets start by drawing the Background Sky + floor
	DrawBackGround(pRenderer);
	DrawWorld(pRenderer);
}

void Renderer::DrawBackGround(SDL_Renderer *pRenderer)
{
	//TODO: Need to read this from some screen object or something
	SDL_Rect sky, floor;
	sky.x = floor.x = 0;
	sky.y = 0;
	floor.y = m_iScreenHight / 2;
	sky.w = floor.w = m_iScreenWidth;
	sky.h = floor.h = m_iScreenHight / 2;

	SDL_SetRenderDrawColor(pRenderer, 46, 46, 46, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(pRenderer, &sky);

	SDL_SetRenderDrawColor(pRenderer, 116, 116, 116, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(pRenderer, &floor);
}

void Renderer::DrawWorld(SDL_Renderer *pRenderer)
{
	float iHlafView = m_pPlayer->GetFieldOfView() / 2;
	float dAngleIncrements = (float)m_pPlayer->GetFieldOfView() / (float)m_iScreenWidth;

	Angle CastAngle;
	CastAngle.Set((m_pPlayer->GetAngle() + iHlafView));
	int iDistanceToProjectionPlane = (m_iScreenWidth / 2) / tan(Angle::DegreesToRadians(m_pPlayer->GetFieldOfView() / 2));
	for (int i = 0; i < m_iScreenWidth; ++i)
	{
		//std::cout << i <<" Angle = " << CastAngle.Get();
		float dDistanceToWall = RayCastAtAngle(CastAngle);
		int iHight = m_pMap->GetUnits() / dDistanceToWall * iDistanceToProjectionPlane;
		//std::cout << ", Hight = " << iHight << std::endl << std::endl;
		DrawWallAt(pRenderer, i, iHight);
		CastAngle.Add(-dAngleIncrements);
	}
}

void Renderer::DrawWallAt(SDL_Renderer *pRenderer, int iRow, int iHight)
{
	int iCenter = m_iScreenHight / 2;
	int iHalfHight = iHight / 2;
	SDL_SetRenderDrawColor(pRenderer, 0, abs((255 - iHight) % 255), 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(pRenderer, iRow, iCenter - iHalfHight, iRow, iCenter + iHalfHight);
}

float Renderer::RayCastAtAngle(Angle& CastAngle)
{

	float dDistanceY = RayCastOnYSteps(CastAngle);
	float dDistanceX = RayCastOnXSteps(CastAngle);

	//return shortest distance
	if (dDistanceX > dDistanceY)
	{
		return dDistanceY;
	}
	else
	{
		return dDistanceX;
	}
}

float Renderer::RayCastOnYSteps(Angle& CastAngle)
{
	//First lets find which cell the player is in
	//Note: I'm making use of int/int lose of precision 
	int iPlayerCellY = m_pPlayer->GetPositionY() / m_pMap->GetUnits();

	//Need to find the first intersection with incremets of 64 on x & y axis
	int iCellYEdge = iPlayerCellY * m_pMap->GetUnits();

	if (CastAngle.IsPointingDown())
	{
		iCellYEdge += m_pMap->GetUnits(); //Look at next cell
	}
	else
	{
		iCellYEdge -= 1; //Look at previous cell
	}

	float dIntersectionX;

	if (CastAngle.IsPointingDown())
	{
		dIntersectionX = iCellYEdge - m_pPlayer->GetPositionY();
	}
	else
	{
		dIntersectionX = m_pPlayer->GetPositionY() - iCellYEdge;
	}

	float fTanAngle = abs(CastAngle.GetTan());

	if (fTanAngle) //Is it zero? you cant devide by zero
	{
		dIntersectionX /= fTanAngle;
	}
	else
	{
		//Dev by small number that is almost zero
		dIntersectionX /= 0.001;
	}

	if (CastAngle.IsPointingRight())
	{
		dIntersectionX = m_pPlayer->GetPositionX() + dIntersectionX;
	}
	else
	{
		dIntersectionX = m_pPlayer->GetPositionX() - dIntersectionX;
	}

	//Fix Y with Map unit increments 
	int iIntersectionCellX = dIntersectionX / m_pMap->GetUnits();
	int iIntersectionCellY = iCellYEdge / m_pMap->GetUnits();

	int iNextIntersectionY = iCellYEdge;

	//std::cout << "\r\n\tYCells = " << iIntersectionCellX << ", " << iIntersectionCellY;

	if (!m_pMap->IsWall(iIntersectionCellX, iIntersectionCellY))
	{
		//There is no wall lets go on!
		float dStepX = m_pMap->GetUnits() / fTanAngle;

		float dNextIntersectionX = dIntersectionX;

		do
		{
			if (CastAngle.IsPointingDown())
			{
				iNextIntersectionY += m_pMap->GetUnits();
			}
			else
			{
				iNextIntersectionY -= m_pMap->GetUnits();
			}


			if (CastAngle.IsPointingRight())
			{
				dNextIntersectionX += dStepX;
			}
			else
			{
				dNextIntersectionX -= dStepX;
			}

			iIntersectionCellX = dNextIntersectionX / m_pMap->GetUnits();
			iIntersectionCellY = iNextIntersectionY / m_pMap->GetUnits();

			//std::cout<< "\r\n\tYCells = " << iIntersectionCellX << ", " << iIntersectionCellY;
		} while (!m_pMap->IsWall(iIntersectionCellX, iIntersectionCellY));
	}

	float fSinAngle = abs(CastAngle.GetSin());
	float dDistance;

	if (CastAngle.IsPointingDown())
	{
		dDistance = (iNextIntersectionY - m_pPlayer->GetPositionY()) / fSinAngle;
	}
	else
	{
		dDistance = (m_pPlayer->GetPositionY() - iNextIntersectionY) / fSinAngle;
	}

	return dDistance;
}

float Renderer::RayCastOnXSteps(Angle& CastAngle)
{
	//Do X
	int iPlayerCellX = m_pPlayer->GetPositionX() / m_pMap->GetUnits();
	int iCellXEdge = iPlayerCellX * m_pMap->GetUnits();

	if (CastAngle.IsPointingRight())
	{
		iCellXEdge += m_pMap->GetUnits(); //Look at next cell
	}
	else
	{
		iCellXEdge -= 1; //Look at previous cell
	}

	float fTanAngle = abs(CastAngle.GetTan());

	float dIntersectionY;

	if (CastAngle.IsPointingRight())
	{
		dIntersectionY = iCellXEdge - m_pPlayer->GetPositionX();
	}
	else
	{
		dIntersectionY = m_pPlayer->GetPositionX() - iCellXEdge;
	}

	dIntersectionY *= fTanAngle;

	if (CastAngle.IsPointingDown())
	{
		dIntersectionY = m_pPlayer->GetPositionY() + dIntersectionY;
	}
	else
	{
		dIntersectionY = m_pPlayer->GetPositionY() - dIntersectionY;
	}

	int iIntersectionCellX = (iCellXEdge / m_pMap->GetUnits());
	int iIntersectionCellY = dIntersectionY / m_pMap->GetUnits();


	int iNextIntersectionX = iCellXEdge;
	//std::cout << "\r\n\tXCells = " << iIntersectionCellX << ", " << iIntersectionCellY;
	if (!m_pMap->IsWall(iIntersectionCellX, iIntersectionCellY))
	{
		//There is no wall lets go on!
		float dStepY = m_pMap->GetUnits() * fTanAngle;
		float dNextIntersectionY = dIntersectionY;
		do
		{
			if (CastAngle.IsPointingRight())
			{
				iNextIntersectionX += m_pMap->GetUnits();
			}
			else
			{
				iNextIntersectionX -= m_pMap->GetUnits();
			}


			if (CastAngle.IsPointingDown())
			{
				dNextIntersectionY += dStepY;
			}
			else
			{
				dNextIntersectionY -= dStepY;
			}

			iIntersectionCellY = dNextIntersectionY / m_pMap->GetUnits();
			iIntersectionCellX = iNextIntersectionX / m_pMap->GetUnits();
			//std::cout << "\r\n\tXCells = " << iIntersectionCellX << ", " << iIntersectionCellY;
		} while (!m_pMap->IsWall(iIntersectionCellX, iIntersectionCellY));
	}

	//TODO: Validate cos value
	float fCosAngle = abs(CastAngle.GetCos());
	float dDistance;

	if (CastAngle.IsPointingRight())
	{
		dDistance = (iNextIntersectionX - m_pPlayer->GetPositionX()) / fCosAngle;
	}
	else
	{
		dDistance = (m_pPlayer->GetPositionX() - iNextIntersectionX) / fCosAngle;
	}

	return dDistance;
}
