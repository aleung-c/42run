# include "../includes/QDrun.hpp"

GamePlayController::GamePlayController() : CurrentScene(MAIN_MENU),
ButtonPressed(false)
{

}

GamePlayController::~GamePlayController()
{

}

GamePlayController&		GamePlayController::Instance()
{
	return (GamePlayController::m_instance);
}

// --------------------------------------------------------------------	//
//																		//
//	Gameplay elements initialization									//
//																		//
// --------------------------------------------------------------------	//

void	GamePlayController::InitGame()
{

	// ----- DEBUG and showcase engine.
	// Character = new GameObject("Character", "./ressources/BasicCriypticman.obj");
	// Character->Position = glm::vec3(3.0, 0.0, 0.0);

	// BasicWall = new GameObject("BasicWall", "./ressources/BasicWall.obj");
	// BasicWall->Position = glm::vec3(1.0, 0.0, 0.0);

	// HelloText = new GameTextObject("HelloText1", "Hello 42 run");
	// HelloText->Position = glm::vec3(0.0, 0.0, 0.0);
	// HelloText->Color = glm::vec3(1.0, 1.0, 1.0);

	// HelloText2 = new GameTextObject("HelloText1", "Hello2pgbcvl");
	// HelloText2->Position = glm::vec3(100.0, 70.0, 0.0);
	// HelloText2->Color = glm::vec3(1.0, 1.0, 1.0);

	// UIElem = new GameUIObject("UIELEM1", "./ressources/UI_Elem_1.bmp");
	// UIElem->Position = glm::vec3(200.0, 120.0, 0.0);
	// UIElem2 = new GameUIObject("UIELEM2", "./ressources/UI_Elem_1.bmp");
	// UIElem2->Position = glm::vec3(600.0, 120.0, 0.0);
	MainCamera = GameEngineController::Instance().GetCamera();
	CameraLookAtPos = GameEngineController::Instance().GetCameraLookAt();

	MainCamera->Position = glm::vec3(0.0, 4.0, -11.0);
	CameraLookAtPos->x = 0.0;
	CameraLookAtPos->y = 0.0;
	CameraLookAtPos->z = 0.0;

	MainMenuBackground = new GameUIObject("MainMenuBack", "./ressources/MainMenuBackground.bmp");
	World.SpawnInitialWorld();
	Character = new GameObject("Character", "./ressources/models/character_idle.obj");
	Character->Position = glm::vec3(3.0, 0.0, -7.0);
	lerpmu = 0.0;
}

// --------------------------------------------------------------------	//
//																		//
//	Gameplay every loop functions										//
//																		//
// --------------------------------------------------------------------	//

/*
**	Launched after the check for events and before the drawing;
*/

void	GamePlayController::Update()
{
	// ----- DEBUG and showcase engine.
	// Character->Rotation.y += 0.001;
	// Character->Position.z += 0.001;
	// BasicWall->Rotation.y += 0.003;

	if (CurrentScene == MAIN_MENU)
	{
		if (ButtonPressed == true)
		{
			// transitionning to ingame;
			if (MainMenuBackground->Position.x < 1280.0)
			{
				MainMenuBackground->Position.x = Tools::CubicInterpolation(MainMenuBackground->Position.x, 1280.0, lerpmu);
				lerpmu += 0.005;
			}
			else
			{
				TransitionDone = true;
				CurrentScene = IN_GAME;
				std::cout << "Go to IN_GAME Scene" << std::endl;
			}

		}
	}
	else if (CurrentScene == IN_GAME)
	{
		World.UpdateWorld();
	}

}

/*
**	Launched last after the drawing.
*/

void	GamePlayController::LateUpdate()
{

}

// --------------------------------------------------------------------	//
//																		//
//	Gameplay event handling												//
//																		//
// --------------------------------------------------------------------	//

// This method is STATIC -> glfw constraint.
void	GamePlayController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;

	 if (action == GLFW_PRESS)
	 {
	 	std::cout << "pressed any key!" << std::endl;
	 	GamePlayController::Instance().ButtonPressed = true;
	 	if (GamePlayController::Instance().CurrentScene == IN_GAME)
	 	{
			// camera placement debug
			if (key == GLFW_KEY_W)
			{
				GamePlayController::Instance().MainCamera->Position.z += 0.5f;
			}
			else if (key == GLFW_KEY_S)
			{
				GamePlayController::Instance().MainCamera->Position.z -= 0.5f;
			}
			else if (key == GLFW_KEY_A)
			{
				GamePlayController::Instance().MainCamera->Position.x += 0.5f;
			}
			else if (key == GLFW_KEY_D)
			{
				GamePlayController::Instance().MainCamera->Position.x -= 0.5f;
			}
			else if (key == GLFW_KEY_SPACE)
			{
				GamePlayController::Instance().MainCamera->Position.y += 0.5f;
			}
			else if (key == GLFW_KEY_C)
			{
				GamePlayController::Instance().MainCamera->Position.y -= 0.5f;
			}
			
			std::cout << "Camera: " << GamePlayController::Instance().MainCamera->Position.x << "x "
				<< GamePlayController::Instance().MainCamera->Position.y << "y "
				<< GamePlayController::Instance().MainCamera->Position.z << "z" << std::endl;
		}
	}
}
