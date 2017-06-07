#ifndef GAMEPLAYCONTROLLER_HPP
# define GAMEPLAYCONTROLLER_HPP

# include "QDrun.hpp"

/*
**	The main class concerning the gameplay.
**	Will handle quite everything from movement to collision,
**	using controller subclasses.
**
**	-> Singleton due to GLFW events handling limitations.
*/

class	GamePlayController
{
	public:
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
		
		GamePlayController();
		~GamePlayController();

		void						InitGame();
		void						ResetGameDatas(t_GameDatas &GameDatas);

		void						OnGameStart();

		// ----- Loop functions
		void						Update();
		void						HandleGameCollision();
		void						LateUpdate();

		// ------ Event methods
		static void					KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void						GameModifier();
		void						ResetGame();

	private:
		float						_lerpmu;
		bool						_onGameStartLaunched;
		static GamePlayController	m_instance;
		bool						_spawnStep1;
		bool						_spawnStep2;
		bool						_spawnStep3;
};

#endif
