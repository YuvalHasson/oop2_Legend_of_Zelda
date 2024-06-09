#include "Controller.h"
int main() try
{
	Controller controller;
	controller.run();
	return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...)
{
	std::cerr << "Unknown exception" << std::endl;
	return EXIT_FAILURE;
}