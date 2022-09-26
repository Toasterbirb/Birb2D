#include "Grid.hpp"

void GenerateGridLines(const Birb::Window& window, Birb::Scene* grid_scene, const Birb::Scene level_scene, const Birb::Vector2int& grid_position_offset, const float& scale, const Birb::Vector2int& dimensions, std::vector<Birb::Line>& horizontal_lines, std::vector<Birb::Line>& vertical_lines)
{
	/* Clear the arrays */
	horizontal_lines.clear();
	vertical_lines.clear();

	Birb::Vector2f scene_target_position = level_scene.Position() + grid_position_offset.toFloat();

	/* Horizontal lines */
	float temp_pos = 0;
	for (int i = 0; i < dimensions.y + 1; i++)
	{
		/* Check if we are outside the view from the top */
		if (scene_target_position.y + temp_pos > 0)
		{
			Birb::Vector2f pointA = { 0, temp_pos };
			Birb::Vector2f pointB = { dimensions.x * scale, temp_pos };
			horizontal_lines.push_back(Birb::Line(pointA, pointB));
		}

		temp_pos += scale;

		/* Check if we are outside the view from the bottom */
		if (scene_target_position.y + temp_pos > window.dimensions.y)
			break;
	}

	/* Vertical lines */
	temp_pos = 0;
	for (int i = 0; i < dimensions.x + 1; i++)
	{
		/* Check if we are outside the view from the left side */
		if (scene_target_position.x + temp_pos > 0)
		{
			Birb::Vector2f pointA = { temp_pos, 0 };
			Birb::Vector2f pointB = { temp_pos, dimensions.y * scale };
			vertical_lines.push_back(Birb::Line(pointA, pointB));
		}

		temp_pos += scale;

		/* Check if we are outside the view from the right side */
		if (scene_target_position.x + temp_pos > window.dimensions.x)
			break;
	}

	grid_scene->Clear();

	/* Add the lines to the scene */
	for (size_t i = 0; i < horizontal_lines.size(); i++)
		grid_scene->AddObject(&horizontal_lines[i]);

	for (size_t i = 0; i < vertical_lines.size(); i++)
		grid_scene->AddObject(&vertical_lines[i]);

	grid_scene->SetPosition(scene_target_position);
}

Birb::Vector2int ClickToIndex(const Birb::Scene& grid_scene, const Birb::Vector2int& dimensions, const Birb::Vector2int& cursor_pos, const float& scale)
{
	Birb::Vector2int result;

	if (cursor_pos.x < grid_scene.Position().x || cursor_pos.y < grid_scene.Position().y)
		return { -1, -1};
	else if (cursor_pos.x > grid_scene.Position().x + (scale * dimensions.x)
			|| cursor_pos.y > grid_scene.Position().y + (scale * dimensions.y))
		return { -1, -1 };

	result = grid_scene.Position().toInt() - cursor_pos;
	result.x /= scale;
	result.y /= scale;

	/* Fix the negative values */
	result.x = std::abs(result.x);
	result.y = std::abs(result.y);

	/* Check if the result is out of bounds */
	if (result.x > dimensions.x - 1 || result.y > dimensions.y - 1)
		return { -1, -1 };

	return result;
}
