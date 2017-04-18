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

	// teapot = new GameObject("Teapot", "./ressources/teapot2.obj");
	// teapot->Position.x = -4.0;
	// teapot->Scale = glm::vec3(4.0, 4.0, 4.0);

	BasicWall = new GameObject("BasicWall", "./ressources/BasicWall.obj");
	BasicWall->Position = glm::vec3(1.0, 0.0, 0.0);

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