#ifndef GAMEPLAYCONTROLLER_HPP
# define GAMEPLAYCONTROLLER_HPP

class GamePlayController
{
	public:
		GameObject					*Character;
		GameObject					*teapot;
		GameObject					*BasicWall;

		GameTextObject				*HelloText;
		GameTextObject				*HelloText2;
		GameUIObject				*UIElem;

		std::vector<GameObject *>	WorldObjects;

		GamePlayController();
		~GamePlayController();

		void	InitGame();

		// loop functions
		void	Update();
		void	LateUpdate();
	
};

#endif