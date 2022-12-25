// DIYWolf3D.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Notes Left hand cordinate system

#include <iostream>

#include "DIYWolf3DEngine.h"


int main(int argc, char* argv[])
{
	DIYWolf3DEngine wolf_3d;

	wolf_3d.Initialize();

	while (!wolf_3d.IsOver())
	{
		wolf_3d.ProcessInput();
		wolf_3d.Update();
		wolf_3d.Render();
		wolf_3d.Delay();
	}

	wolf_3d.Clean();

	return 0;
}

