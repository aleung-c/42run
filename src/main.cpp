#include "../includes/QDrun.hpp"

GamePlayController GamePlayController::m_instance = GamePlayController();

int		main(void)
{
	GlobalGameController	GameController;

	std::cout << "Hello 42run" << std::endl;
	GameController.GameEngine = &GameEngineController::Instance();
	GameController.InitGame();
	GameController.MainLoop();
	return 0;
}
