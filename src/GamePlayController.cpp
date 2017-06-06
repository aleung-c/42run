# include "../includes/QDrun.hpp"

GamePlayController::GamePlayController()
:	
	CurrentScene(MAIN_MENU),
	OnGameStartLaunched(false),
	CollidingObject(NULL),
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

void		GamePlayController::InitGame()
{

	// ----- DEBUG and showcase engine.
	// Character = new GameObject("Character", "./ressources/BasicCriypticman.obj");
	// Character->Transform.Position = glm::vec3(3.0, 0.0, 0.0);

	// BasicWall = new GameObject("BasicWall", "./ressources/BasicWall.obj");
	// BasicWall->Transform.Position = glm::vec3(1.0, 0.0, 0.0);

	// HelloText = new GameTextObject("HelloText1", "Hello 42 run");
	// HelloText->Transform.Position = glm::vec3(0.0, 0.0, 0.0);
	// HelloText->Color = glm::vec3(1.0, 1.0, 1.0);

	// HelloText2 = new GameTextObject("HelloText1", "Hello2pgbcvl");
	// HelloText2->Transform.Position = glm::vec3(100.0, 70.0, 0.0);
	// HelloText2->Color = glm::vec3(1.0, 1.0, 1.0);

	// UIElem = new GameUIObject("UIELEM1", "./ressources/UI_Elem_1.bmp");
	// UIElem->Transform.Position = glm::vec3(200.0, 120.0, 0.0);
	// UIElem2 = new GameUIObject("UIELEM2", "./ressources/UI_Elem_1.bmp");
	// UIElem2->Transform.Position = glm::vec3(600.0, 120.0, 0.0);
	GameEngineController::Instance().DebugMode = true;
	MainCamera = GameEngineController::Instance().GetCamera();
	CameraLookAtPos = GameEngineController::Instance().GetCameraLookAt();

	MainCamera->Transform.Position = glm::vec3(0.0, 6, -10.5);
	CameraLookAtPos->x = 0.0;
	CameraLookAtPos->y = 1.0;
	CameraLookAtPos->z = 8.0;

	MainMenuBackground = new GameUIObject("MainMenuBack", "./ressources/MainMenuBackground.bmp");
	World.InitObstacles();
	World.InitTextureVariations();
	World.SpawnInitialWorld();
	Character.InitCharacter(glm::vec3(0.0, 0.0, -3.0));
	lerpmu = 0.0;

	CollisionController.InitGameCollisions(&Character, &World);
}

void			GamePlayController::OnGameStart()
{
	// start the character running animation
	Character.SetRunAnimation();
	UI.InitUI();
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
	// Character->Transform.Rotation.y += 0.001;
	// Character->Transform.Position.z += 0.001;
	// BasicWall->Transform.Rotation.y += 0.003;

	if (CurrentScene == MAIN_MENU)
	{
		if (ButtonPressed == true)
		{
			// transitionning to ingame;
			if (MainMenuBackground->Transform.Position.x < 1280.0)
			{
				MainMenuBackground->Transform.Position.x = Tools::LinearInterpolation(MainMenuBackground->Transform.Position.x, 1280.0, lerpmu);
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
		if (OnGameStartLaunched == false)
		{
			OnGameStart();
			OnGameStartLaunched = true;
		}
		World.UpdateWorld();
		Character.Update();
		if ((CollidingObject = CollisionController.PlayerCollides()))
		{
			std::cout << "COLLISION WITH " << CollidingObject->Name << std::endl;
		}
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
	// 			GameInstance->MainCamera->Transform.Position.z += 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_S)
	// 		{
	// 			GameInstance->MainCamera->Transform.Position.z -= 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_A)
	// 		{
	// 			GameInstance->MainCamera->Transform.Position.x += 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_D)
	// 		{
	// 			GameInstance->MainCamera->Transform.Position.x -= 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_SPACE)
	// 		{
	// 			GameInstance->MainCamera->Transform.Position.y += 0.5f;
	// 		}
	// 		else if (key == GLFW_KEY_C)
	// 		{
	// 			GameInstance->MainCamera->Transform.Position.y -= 0.5f;
	// 		}
			
	// 		std::cout << "Camera: " << GameInstance->MainCamera->Transform.Position.x << "x "
	// 			<< GameInstance->MainCamera->Transform.Position.y << "y "
	// 			<< GameInstance->MainCamera->Transform.Position.z << "z" << std::endl;
	// 	}
	// }
}
