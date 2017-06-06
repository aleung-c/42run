#ifndef GAMEPLAYCONTROLLER_HPP
# define GAMEPLAYCONTROLLER_HPP

# include "QDrun.hpp"

class GamePlayController
{
	public:
		// ----- DEBUG and showcase engine.
		// GameObject				*Character;
		// GameObject				*BasicWall;

		// GameTextObject			*HelloText;
		// GameTextObject			*HelloText2;
		// GameUIObject				*UIElem;
		// GameUIObject				*UIElem2;s

		// lazy singleton for c language glfw key callback.
		static GamePlayController&			Instance();

		// ----- Gameplay controller elements
		t_GameScene					CurrentScene;
		t_GameDatas					GameDatas;

		GameObject					*MainCamera;
		glm::vec3					*CameraLookAtPos;

		

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
		void						ResetGameDatas(t_GameDatas &GameDatas);

		void						OnGameStart();

		// ----- Loop functions
		void						Update();
		void						LateUpdate();

		// ------ Event methods
		static void					KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void						GameModifier(t_GameDatas &GameDatas);

	private:
		bool						_onGameStartLaunched;
		static GamePlayController	m_instance;
};

#endif