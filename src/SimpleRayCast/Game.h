#pragma once

#include <string>

#include <SDL.h>

#include "Player.h"
#include "Map.h"
#include "Renderer.h"

class Game
{
public:
  Game();
  ~Game();

  bool Init(int iMaxFrameRatePerSec);
  bool IsRunning();

  int Execute();

  void HandleEvents();
  void Loop();
  void Render();
  void Cleanup();

protected:
  void Log(std::string strLog);

  bool m_bRunning;
  unsigned  int m_iFrameRate;
  SDL_Renderer *m_pRenderer;
  SDL_Window *m_pWindow;

  Player m_Player;
  Map m_Map;
  Renderer m_Renderer;
};
