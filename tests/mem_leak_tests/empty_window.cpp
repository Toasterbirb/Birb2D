#include "Renderwindow.hpp"
#include "Vector/Vector2Int.hpp"
#include <iostream>

int main(void)
{
	std::cout << " > Create an empty window and quit the program immediately" << std::endl;
	Birb::Window window("Window title", Birb::Vector2Int(960, 540), 60, false);
	return 0;
}
