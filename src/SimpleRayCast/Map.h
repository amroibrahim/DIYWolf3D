#pragma once

#include<vector>

class Map
{
public:
	enum ObjectType
	{
		EEMPTY,
		EWALL
	};

	Map(int iWidth, int iHight, int iGridUnits);
	~Map();

	int GetMapWidth();
	int GetMapHight();
	int GetUnits();

	bool IsWall(int iPostionX, int iPostionY);

	ObjectType GetObjectAt(int iPostionX, int iPostionY);

protected:
	int m_iUnits;
	int m_iCellMapWidth;
	int m_iCallMapHight;
	std::vector<std::vector<ObjectType>> m_vMap;
};

