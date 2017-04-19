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
		GameUIObject				*UIElem2;


		std::vector<GameObject *>	WorldObjects;

		// Game Rule values
		float						WorldSpeed;
		float						MaxWorldX;
		float						MinWorldX;

		GamePlayController();
		~GamePlayController();

		void	InitGame();

		// Loop functions
		void	Update();
		void	LateUpdate();

		// Event methods
		void	KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif