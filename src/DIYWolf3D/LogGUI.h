#pragma once

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

class LogGUI
{
public:
	void Log(const char* format, ...);
	void Render(const char* title, bool* p_opened = NULL);
	void Clear();

protected:
	ImGuiTextBuffer log_buffer_;
	ImGuiTextFilter filter_;
	ImVector<int> line_offsets_;
	bool scroll_bottom_;
};
