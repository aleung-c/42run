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

	MainCamera->Position = glm::vec3(0.0, 4.5, -10.5);
	CameraLookAtPos->x = 0.0;
	CameraLookAtPos->y = 1.0;
	CameraLookAtPos->z = 8.0;

	MainMenuBackground = new GameUIObject("MainMenuBack", "./ressources/MainMenuBackground.bmp");
	World.SpawnInitialWorld();
	
	Character.InitCharacter(glm::vec3(3.0, 0.0, 0.0));
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
				MainMenuBackground->Position.x = Tools::LinearInterpolation(MainMenuBackground->Position.x, 1280.0, lerpmu);
				lerpmu += 0.005;
			}
			else
			{
				TransitionDone = true;
				lerpmu = 0.0;
				CurrentScene = IN_GAME;
				std::cout << "Go to IN_GAME Scene" << std::endl;
			}

		}
	}
	else if (CurrentScene == IN_GAME)
	{
		World.UpdateWorld();
		Character.Update();
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
// It forced me to make the GamePlayController a singleton instance...
void	GamePlayController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static GamePlayController	*GameInstance;

	GameInstance = &GamePlayController::Instance();

	if (GameInstance->CurrentScene == IN_GAME)
	{
		GameInstance->Character.HandleControls(window, key, scancode, action, mods);
	}
	else if (action == GLFW_PRESS)
	{
		GameInstance->ButtonPressed = true;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		std::cout << "Exiting 42run ..." << std::endl;
		exit(0);
	}

	// // Camera displacing tests
	// if (action == GLFW_PRESS)
	// {
	// 	std::cout << "pressed any key!" << std::endl;
	// 	GameInstance->ButtonPressed = true;
	// 	if (GameInstance->CurrentScene == IN_GAME)
	//  	{
	// 		// camera placement debug
	// 		if (key == GLFW_KEY_W)
	// 		{
	// 			GameInstance->MainCamera->Position.z += 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_S)
	// 		{
	// 			GameInstance->MainCamera->Position.z -= 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_A)
	// 		{
	// 			GameInstance->MainCamera->Position.x += 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_D)
	// 		{
	// 			GameInstance->MainCamera->Position.x -= 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_SPACE)
	// 		{
	// 			GameInstance->MainCamera->Position.y += 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_C)
	// 		{
	// 			GameInstance->MainCamera->Position.y -= 0.5f;
	// 		}
			
	// 		std::cout << "Camera: " << GameInstance->MainCamera->Position.x << "x "
	// 			<< GameInstance->MainCamera->Position.y << "y "
	// 			<< GameInstance->MainCamera->Position.z << "z" << std::endl;
	// 	}
	// }
}
