#include "LogGUI.h"

void LogGUI::Log(const char* format, ...)
{
	int old_size = log_buffer_.size();
	va_list args;

	va_start(args, format);
	log_buffer_.appendfv(format, args);
	va_end(args);

	for (int new_size = log_buffer_.size(); old_size < new_size; old_size++)
	{
		if (log_buffer_[old_size] == '\n')
		{
			line_offsets_.push_back(old_size);
		}
	}
	scroll_bottom_ = true;
}

void LogGUI::Render(const char* title, bool* p_opened /*= NULL*/)
{
	ImGui::SetNextWindowSize(ImVec2(500, 300));
	ImGui::Begin(title, p_opened);
	if (ImGui::Button("Clear"))
	{
		Clear();
	}

	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	filter_.Draw("Filter", -100.0f);

	ImGui::Separator();
	ImGui::BeginChild("scrolling");
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
	if (copy)
	{
		ImGui::LogToClipboard();
	}

	if (filter_.IsActive())
	{
		const char* buffer_begin = log_buffer_.begin();
		const char* line = buffer_begin;
		for (int line_no = 0; line != NULL; line_no++)
		{
			const char* line_end = (line_no < line_offsets_.Size) ? buffer_begin + line_offsets_[line_no] : NULL;
			if (filter_.PassFilter(line, line_end))
			{
				ImGui::TextUnformatted(line, line_end);
			}

			line = line_end && line_end[1] ? line_end + 1 : NULL;
		}
	}
	else
	{
		ImGui::TextUnformatted(log_buffer_.begin());
	}

	if (scroll_bottom_)
	{
		ImGui::SetScrollHereY(1.0f);
	}

	scroll_bottom_ = false;
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::End();
}

void LogGUI::Clear()
{
	log_buffer_.clear();
	line_offsets_.clear();
}
