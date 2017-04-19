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
	Character = new GameObject("Character", "./ressources/BasicCriypticman.obj");
	Character->Position = glm::vec3(3.0, 0.0, 0.0);

	// // teapot = new GameObject("Teapot", "./ressources/teapot2.obj");
	// // teapot->Position.x = -4.0;
	// // teapot->Scale = glm::vec3(4.0, 4.0, 4.0);

	BasicWall = new GameObject("BasicWall", "./ressources/BasicWall.obj");
	BasicWall->Position = glm::vec3(1.0, 0.0, 0.0);

	HelloText = new GameTextObject("HelloText1", "Hello 42 run");
	HelloText->Position = glm::vec3(0.0, 0.0, 0.0);
	HelloText->Color = glm::vec3(1.0, 1.0, 1.0);

	HelloText2 = new GameTextObject("HelloText1", "Hello2pgbcvl");
	HelloText2->Position = glm::vec3(100.0, 70.0, 0.0);
	HelloText2->Color = glm::vec3(1.0, 1.0, 1.0);

	UIElem = new GameUIObject("UIELEM1", "./ressources/UI_Elem_1.bmp");
	UIElem->Position = glm::vec3(200.0, 120.0, 0.0);
	// UIElem2 = new GameUIObject("UIELEM2", "./ressources/UI_Elem_1.bmp");
	// UIElem2->Position = glm::vec3(600.0, 120.0, 0.0);
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
	Character->Rotation.y += 0.001;
	Character->Position.z += 0.02;
	BasicWall->Rotation.y += 0.003;
}

/*
**	Launched last after the drawing.
*/

void	GamePlayController::LateUpdate()
{

}