#include "TextureManager.h"

#include <string>

#include <SDL_image.h>


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::Initialize()
{
	std::vector<std::string> texture_list;
	texture_list.push_back("../../assets/BRICK_1A.png");
	texture_list.push_back("../../assets/BRICK_2A.png");
	texture_list.push_back("../../assets/BRICK_3A.png");
	texture_list.push_back("../../assets/BRICK_4D.png");

	for (int i = 0; i < texture_list.size(); ++i)
	{
		// Convert the surface to match the format we use
		SDL_Surface* loaded_serface = IMG_Load(texture_list[i].c_str());
		m_Textures.push_back(SDL_ConvertSurfaceFormat(loaded_serface, pixel_format_, 0));
		SDL_FreeSurface(loaded_serface);
	}
}

void TextureManager::SetFormat(Uint32 pixel_format)
{
	pixel_format_ = pixel_format;
}

SDL_Surface* TextureManager::getTextureBuffer(int id)
{
	--id;
	if (id < 0 || m_Textures.size() <= id)
	{
		return nullptr;
	}

	return m_Textures[id];
}

void TextureManager::Clean()
{
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		SDL_FreeSurface(m_Textures[i]);
	}

	m_Textures.clear();
}
