#pragma once
#include "Birb2D.hpp"

void GenerateGridLines(const Birb::Window& window, Birb::Scene* grid_scene, const Birb::Scene level_scene, const Birb::Vector2int& grid_position_offset, const float& scale, const Birb::Vector2int& dimensions, std::vector<Birb::Line>& horizontal_lines, std::vector<Birb::Line>& vertical_lines);
Birb::Vector2int ClickToIndex(const Birb::Scene& grid_scene, const Birb::Vector2int& dimensions, const Birb::Vector2int& cursor_pos, const float& scale);
