#include "Map.h"

Map::Map(int iWidth, int iHight, int iGridUnits)
{
	m_iCellMapWidth = iWidth;
	m_iCallMapHight = iHight;
	m_iUnits = iGridUnits;

	m_vMap.resize(iHight, std::vector<ObjectType>(iWidth, ObjectType::EEMPTY));

	//TODO: Temp/Test code
	for (int i = 0; i < iWidth; ++i)
	{
		m_vMap[0][i] = EWALL; //top
		m_vMap[iHight - 1][i] = EWALL; //bottom
		m_vMap[i][0] = EWALL; //Left
		m_vMap[i][iWidth - 1] = EWALL; //bottom
	}

	m_vMap[2][5] = EWALL;
	m_vMap[2][6] = EWALL;
	m_vMap[2][7] = EWALL;
	m_vMap[3][7] = EWALL;
	m_vMap[4][5] = EWALL;
	m_vMap[4][6] = EWALL;
	m_vMap[4][7] = EWALL;
}

Map::~Map()
{
}

int Map::GetMapWidth()
{
	return m_iCellMapWidth;
}

int Map::GetMapHight()
{
	return m_iCallMapHight;
}

int Map::GetUnits()
{
	return m_iUnits;
}

Map::ObjectType Map::GetObjectAt(int iPostionX, int iPostionY)
{
	return m_vMap[iPostionY][iPostionX];
}

bool Map::IsWall(int iPostionX, int iPostionY)
{
	//TODO: Check if you out of map (any thing out of map is a wall
	if (0 > iPostionX || iPostionX >= m_iCellMapWidth || 0 > iPostionY || iPostionY >= m_iCallMapHight)
	{
		return true;
	}

	return (m_vMap[iPostionY][iPostionX] == EWALL);
}