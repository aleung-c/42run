# include "../includes/QDrun.hpp"

GamePlayController::GamePlayController()
{

}

GamePlayController::~GamePlayController()
{

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

	MainCamera->Position = glm::vec3(0.0, 2.0, -10.0);
	CameraLookAtPos->x = 0.0;
	CameraLookAtPos->y = 0.0;
	CameraLookAtPos->z = 0.0;
	World.SpawnInitialWorld();
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
	World.UpdateWorld();
	// CameraLookAtPos->x += 0.01;
	// ----- DEBUG and showcase engine.
	// Character->Rotation.y += 0.001;
	// Character->Position.z += 0.001;
	// BasicWall->Rotation.y += 0.003;
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

void	GamePlayController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
}
