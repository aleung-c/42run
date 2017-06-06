#ifndef GAMEPLAYCONTROLLER_HPP
# define GAMEPLAYCONTROLLER_HPP

# include "QDrun.hpp"

class GamePlayController
{
	public:
		// ----- DEBUG and showcase engine.
		// GameObject					*Character;
		// GameObject					*BasicWall;

		// GameTextObject				*HelloText;
		// GameTextObject				*HelloText2;
		// GameUIObject				*UIElem;
		// GameUIObject				*UIElem2;

		// lazy singleton for c langage key callback.
		static GamePlayController&			Instance();

		// Gameplay controller elements
		t_GameScene					CurrentScene;

		GameObject					*MainCamera;
		glm::vec3					*CameraLookAtPos;

		bool						OnGameStartLaunched;

		// ----- Controllers
		WorldController				World;
		CharacterController			Character;
		UIController				UI;

		GameCollisionController		CollisionController;
		GameObject					*CollidingObject;

		// ----- Scene variables
		GameUIObject				*MainMenuBackground;
		bool						ButtonPressed;
		bool						TransitionDone;
		float						lerpmu;

		GamePlayController();
		~GamePlayController();

		void						InitGame();

		void						OnGameStart();

		// Loop functions
		void						Update();
		void						LateUpdate();

		// Event methods
		static void					KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	private:
		static GamePlayController	m_instance;
};

#endif