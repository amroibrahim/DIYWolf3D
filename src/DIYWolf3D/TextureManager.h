#pragma once

#include <SDL.h>
#include <vector>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void Initialize();
	void SetFormat(Uint32 pixel_format);
	SDL_Surface* getTextureBuffer(int id);
	void Clean();

protected:
	std::vector<SDL_Surface*> m_Textures;
	Uint32 pixel_format_;
};

