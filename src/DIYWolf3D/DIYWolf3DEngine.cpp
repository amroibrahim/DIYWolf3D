#include "DIYWolf3DEngine.h"

#include <iostream>

DIYWolf3DEngine::DIYWolf3DEngine() :
	is_over_(false),
	screen_width_(320),
	screen_height_(200),
	window_(nullptr),
	renderer_(nullptr),
	frame_length_(10),
	settings_gui_(&configuration_, &player_),
	player_(&configuration_, &level_),
	ray_caster_(&configuration_, &texture_manager_, &level_, &player_),
	mini_map_(&configuration_, &player_, &level_, &ray_caster_)

{
	screen_width_ = configuration_.display.screen_buffer_width;
	screen_height_ = configuration_.display.screen_buffer_height;
	frame_length_ = 1000 / configuration_.display.framerate;
}

void DIYWolf3DEngine::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}

	window_ = SDL_CreateWindow("DIYWolf3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width_, screen_height_, SDL_WINDOW_SHOWN);

	if (window_ == NULL)
	{
		std::cout << "SDL failed to create window! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, 0);

	if (!renderer_)
	{
		std::cout << "SDL failed to create renderer! SDL_Error: " << SDL_GetError() << std::endl;
	}

	main_surface_ = CreateSurfaceBuffer(configuration_.display.back_buffer_width, configuration_.display.back_buffer_hight);

	configuration_.display.window = window_;
	configuration_.render.renderer = renderer_;

	settings_gui_.Initialize(window_, renderer_);

	ray_caster_.Initialize();
	ray_caster_.SetSurface(main_surface_);

	mini_map_.Initialize();
	
	texture_manager_.SetFormat(main_surface_->format->format);
	texture_manager_.Initialize();
}

void DIYWolf3DEngine::Clean()
{
	mini_map_.Clean();
	settings_gui_.Clean();
	texture_manager_.Clean();

	SDL_FreeSurface(main_surface_);
	main_surface_ = nullptr;

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_Quit();
}

DIYWolf3DEngine::~DIYWolf3DEngine()
{
}

void DIYWolf3DEngine::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		settings_gui_.ProcessEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			Quit();
			break;

		default:
			break;
		}
	}

	// Process key without repeat delays
	KeyPress(SDL_GetKeyboardState(NULL));
}

void DIYWolf3DEngine::Update()
{
	frame_length_ = 1000 / configuration_.display.framerate;
	float elapsed_time = SDL_GetTicks() - last_frame_time_;
	last_frame_time_ = SDL_GetTicks();

	player_.Update(elapsed_time);
	settings_gui_.Update();
	ray_caster_.Update(elapsed_time);
}

bool DIYWolf3DEngine::IsOver()
{
	return is_over_;
}

void DIYWolf3DEngine::Delay()
{
	int32_t current_frame_length_ = SDL_GetTicks() - last_frame_time_;
	if (frame_length_ > current_frame_length_)
	{
		SDL_Delay(frame_length_ - current_frame_length_);
	}
}

void DIYWolf3DEngine::Render()
{
	//SDL_SetRenderDrawColor(renderer_, configuration_.render.sky_color_r, configuration_.render.sky_color_g, configuration_.render.sky_color_b, 255);
	//SDL_RenderClear(renderer_);

	ray_caster_.Render();

	if (configuration_.game.mini_map_enabled)
	{
		mini_map_.Render();
	}

	//player_.Render();

	settings_gui_.Render();
	SDL_RenderPresent(renderer_);
}

void  DIYWolf3DEngine::Quit()
{
	is_over_ = true;
}

void DIYWolf3DEngine::KeyPress(const Uint8* key_states)
{
	if (key_states[SDL_SCANCODE_RIGHT])
	{
		player_.rotation_direction = 1;
	}

	if (key_states[SDL_SCANCODE_LEFT])
	{
		player_.rotation_direction = -1;
	}

	if (key_states[SDL_SCANCODE_UP])
	{
		player_.move_direction = 1;
	}

	if (key_states[SDL_SCANCODE_DOWN])
	{
		player_.move_direction = -1;
	}
}

SDL_Surface* DIYWolf3DEngine::CreateSurfaceBuffer(int width, int hight)
{
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	return SDL_CreateRGBSurface(0, width, hight, 32, rmask, gmask, bmask, amask);
}
