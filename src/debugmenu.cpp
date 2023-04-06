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
		info.angle 	= &entity.angle;
		_entities.push_back(info);
	}

	void DebugMenu::AddEntity(Entity::Text& text_entity)
	{

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
						ImGui::PushItemWidth(70);
						if (ImGui::CollapsingHeader(DebugMenu::_entities[i].name->c_str()))
						{
							ImGui::Text("Rect");
							ImGui::DragFloat("x", &DebugMenu::_entities[i].rect->x);
							ImGui::SameLine();
							ImGui::DragFloat("y", &DebugMenu::_entities[i].rect->y);
							ImGui::SameLine();
							ImGui::DragFloat("w", &DebugMenu::_entities[i].rect->w);
							ImGui::SameLine();
							ImGui::DragFloat("h", &DebugMenu::_entities[i].rect->h);
							ImGui::SameLine();

							ImGui::Spacing();
							ImGui::Spacing();

							ImGui::DragFloat("Angle", DebugMenu::_entities[i].angle);
						}
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
