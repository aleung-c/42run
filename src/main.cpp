#include "../includes/QDrun.hpp"

int		main(void)
{
	GlobalGameController	GameController;

	std::cout << "Hello 42run" << std::endl;
	GameController.InitGame();
	GameController.MainLoop();
	return 0;
}
