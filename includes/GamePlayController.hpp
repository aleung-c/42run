#ifndef GAMEPLAYCONTROLLER_HPP
# define GAMEPLAYCONTROLLER_HPP

class GamePlayController
{
	public:
		GameObject					*Character;
		GameObject					*teapot;
		GameObject					*BasicWall;

		std::vector<GameObject *>	WorldObjects;

		GamePlayController();
		~GamePlayController();

		void	InitGame();

		// loop functions
		void	Update();
		void	LateUpdate();
	
};

#endif