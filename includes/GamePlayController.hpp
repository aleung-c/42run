#ifndef GAMEPLAYCONTROLLER_HPP
# define GAMEPLAYCONTROLLER_HPP

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

		WorldController				World;
		CharacterController			Character;

		GameCollisionController		CollisionController;
		GameObject					*CollidingObject;

		GameUIObject				*MainMenuBackground;
		bool						ButtonPressed;
		bool						TransitionDone;
		float						lerpmu;

		GamePlayController();
		~GamePlayController();

		void						InitGame();

		// Loop functions
		void						Update();
		void						LateUpdate();

		// Event methods
		static void					KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	private:
		static GamePlayController	m_instance;
};

#endif