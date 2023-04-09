#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"

#include "DebugMenu.hpp"
#include "Utils.hpp"

namespace Birb
{
	EntityInfo::EntityInfo()
	:deleted(false)
	{}

	void DebugMenu::AddEntity(BaseEntity& entity)
	{
		EntityInfo info;
		info.name 	= &entity.name;
		info.rect 	= &entity.rect;

		/* Load the color in */
		info.rect_color[0] = entity.rect.color.r / 255.0f;
		info.rect_color[1] = entity.rect.color.g / 255.0f;
		info.rect_color[2] = entity.rect.color.b / 255.0f;
		info.rect_color[3] = entity.rect.color.a / 255.0f;

		info.angle 	= &entity.angle;
		_entities.push_back(info);
	}

	void DebugMenu::Clear()
	{
		_entities.clear();
	}

	void DebugMenu::EntityMenu()
	{
		ImGui::Begin("Entity list");

		/* Create collapse menu for each entity that has a name other than "Default Entity" */
		for (size_t i = 0; i < DebugMenu::_entities.size(); ++i)
		{
			if (!DebugMenu::_entities[i].deleted)
			{
				if (*DebugMenu::_entities[i].name != "Default Entity")
				{
					// BaseEntities
					if (_entities.size() > 0)
					{
						ImGui::PushID(i);
						if (ImGui::CollapsingHeader(DebugMenu::_entities[i].name->c_str()))
						{
							{
								ImGui::PushItemWidth(70);
								ImGui::Text("Rect");

								ImGui::DragFloat("x", &_entities[i].rect->x);
								ImGui::SameLine();
								ImGui::DragFloat("y", &_entities[i].rect->y);
								ImGui::SameLine();
								ImGui::DragFloat("w", &_entities[i].rect->w);
								ImGui::SameLine();
								ImGui::DragFloat("h", &_entities[i].rect->h);
							}

							ImGui::PushItemWidth(240);
							ImGui::ColorEdit3("Color", _entities[i].rect_color);
							ImGui::SameLine();
							if (ImGui::Button("Apply"))
							{
								_entities[i].rect->color.r = 255 * _entities[i].rect_color[0];
								_entities[i].rect->color.g = 255 * _entities[i].rect_color[1];
								_entities[i].rect->color.b = 255 * _entities[i].rect_color[2];
								_entities[i].rect->color.a = 255 * _entities[i].rect_color[3];
							}

							ImGui::Spacing();
							ImGui::Spacing();

							ImGui::PushItemWidth(70);
							ImGui::DragFloat("Angle", DebugMenu::_entities[i].angle);
						}
						ImGui::PopID();
					}
				}
			}
		}

		ImGui::End();
	}

	void DebugMenu::ResouceMonitor(const Diagnostics::ResourceMonitor& statistics, const TimeStep& timeStep)
	{
		ImGui::Begin("Resource monitor");

		ImGui::Text("FPS: %s", utils::CleanDecimals(Math::Round(statistics.fps, 2)).c_str());
		ImGui::Text("FPS avg.: %s", utils::CleanDecimals(Math::Round(statistics.fps_average, 2)).c_str());
		ImGui::Text("FPS 1%% low: %s", utils::CleanDecimals(Math::Round(statistics.lowest_framerate, 2)).c_str());
		ImGui::Text("Framebudget: %s%%", utils::CleanDecimals(Math::Round(timeStep.FrameBudget(), 1)).c_str());
		ImGui::Text("Entity count: %d", statistics.EntityCount);
		ImGui::Spacing();

		ImGui::BeginChild("Memory usage");
		ImGui::Text("Memory usage: %ld MB", statistics.resident_memory_usage / 1024);
		ImGui::EndChild();

		ImGui::End();
	}
}
