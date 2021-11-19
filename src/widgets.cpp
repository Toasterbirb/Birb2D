#include "../include/Widgets.hpp"
#include "../include/Font.hpp"
#include "../include/Utils.hpp"

Widget::TopBar::TopBar(RenderWindow p_window, int barHeight, SDL_Color p_backgroundColor, Font font)
:window(p_window), backgroundColor(p_backgroundColor)
{
	dimensions.w = window.getDimensions().x;
	dimensions.h = barHeight;
	Texture textTexture = window.renderStaticTextTexture("Birb2D", font);

	Entity titleEntity("Title", Vector2f(5, 10), Vector2f(textTexture.dimensions.x, textTexture.dimensions.y), textTexture);
	title = titleEntity;
}

void Widget::TopBar::refresh(Vector2int windowDimensions)
{
	dimensions.w = windowDimensions.x;
	dimensions.x = 0;
	dimensions.y = 0;

	window.DrawRect(Widget::Colors::White, dimensions);
	window.render(title);
}
