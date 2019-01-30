#include <iostream>

#include "Game.h"

Game::Game() : m_bRunning(false), m_pRenderer(nullptr), m_pWindow(nullptr), m_Player(60), m_Map(10, 10, 64), m_iFrameRate(60), m_Renderer(320, 200)
{
}

Game::~Game()
{
}

bool Game::IsRunning()
{
	return m_bRunning;
}

bool Game::Init(int iMaxFrameRatePerSec = 60)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	m_pWindow = SDL_CreateWindow("SimpleRayCast", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 200, SDL_WINDOW_SHOWN);

	if (m_pWindow != nullptr)
	{
		m_bRunning = true;
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(m_pRenderer);
		SDL_RenderPresent(m_pRenderer);
	}
	else
	{
		return false;
	}

	//Initilize the raycast renderer with object it needs
	if (!m_Renderer.Init(&m_Player, &m_Map))
	{
		return false;
	}

	//TODO: Do some data loading and set values 
	m_Player.SetAngle(0);// 134
	m_Player.SetPositionX(270);
	m_Player.SetPositionY(300);

	return true;
}

int Game::Execute()
{
	//Initialise
	if (Init() == false)
	{
		Log("Faild to Init!");
		return -1;
	}

	unsigned int iFrameMS = 1000 / m_iFrameRate;

	while (IsRunning())
	{
		//Read Start time
		unsigned int iStartMS = SDL_GetTicks();

		//Get Input
		HandleEvents();

		//Do Physics
		Loop();

		//Render
		Render();

		//Read End time and wait for the next frame
		int iDelayMs = iFrameMS - (SDL_GetTicks() - iStartMS);
		if (iDelayMs > 0)
		{
			SDL_Delay(iDelayMs);
		}
	}

	//Exit and cleanup
	Cleanup();

	return 0;
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_UP)
				m_Player.MoveForward();
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
				m_Player.MoveBackward();
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				m_Player.RotateLeft();
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				m_Player.RotateRight();

			std::cout << "(" << m_Player.GetPositionX() << "," << m_Player.GetPositionY() << ") Ang=" << m_Player.GetAngle() << " Cel=" << "[" << (int)m_Player.GetPositionX() / 64 << ","
				<< (int)m_Player.GetPositionY() / 64 << "] S=" << m_Player.m_Angle.GetSin() << " C=" << m_Player.m_Angle.GetCos() << " T=" << m_Player.m_Angle.GetTan() << std::endl;
			break;

		default:
			break;
		}
	}
}

void Game::Loop()
{

}

void Game::Render()
{
	m_Renderer.RenderView(m_pRenderer);
	SDL_UpdateWindowSurface(m_pWindow);
}

void Game::Cleanup()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::Log(std::string strLog)
{
	std::cout << strLog << std::endl;
}
