#pragma once
#include "Birb2D.hpp"

void GenerateGridLines(const Birb::Window& window, Birb::Scene* grid_scene, const Birb::Scene level_scene, const Birb::Vector2Int& grid_position_offset, const float& scale, const Birb::Vector2Int& dimensions, std::vector<Birb::Line>& horizontal_lines, std::vector<Birb::Line>& vertical_lines);
Birb::Vector2Int ClickToIndex(const Birb::Scene& grid_scene, const Birb::Vector2Int& dimensions, const Birb::Vector2Int& cursor_pos, const float& scale);
