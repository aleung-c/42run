# include "../includes/QDrun.hpp"

GamePlayController::GamePlayController()
:	
	CurrentScene(MAIN_MENU),
	CollidingObject(NULL),
	ButtonPressed(false),
	_onGameStartLaunched(false)

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
	// Game Mechanics initialization.
	MainCamera = GameEngineController::Instance().GetCamera();
	CameraLookAtPos = GameEngineController::Instance().GetCameraLookAt();

	MainCamera->Transform.Position = glm::vec3(0.0, 6, -10.5);
	CameraLookAtPos->x = 0.0;
	CameraLookAtPos->y = 1.0;
	CameraLookAtPos->z = 8.0;

	MainMenuBackground = new GameUIObject("MainMenuBack", "./ressources/MainMenuBackground.bmp");
	World.InitObstacles();
	World.InitCoins();
	World.InitTextureVariations();
	World.SpawnInitialWorld();
	Character.InitCharacter(glm::vec3(0.0, 0.0, -3.0));
	Character.CharacterCollider->Visible = false;
	_lerpmu = 0.0;

	CollisionController.InitGameCollisions(&Character, &World);

	// Gameplay Initialisation
	ResetGameDatas(GameDatas);
	UI.InitUI();
}

void			GamePlayController::ResetGameDatas(t_GameDatas &GameDatas)
{
	GameDatas.PlayerLife = 3;
	GameDatas.PlayerCoins = 0;
	GameDatas.DifficultyStep = 100.0;
	GameDatas.Distance = 0.0;
	GameDatas.CurDistanceStep = 0.0;
}

/*
**	Launched when the running game start (scene = IN_GAME)
*/

void			GamePlayController::OnGameStart()
{
	Character.SetRunAnimation();
	UI.ShowUI();
	World.Move();
	// World Spawn timers reset
	World.Start = std::chrono::system_clock::now();
	World.CoinStart = std::chrono::system_clock::now();
}

// --------------------------------------------------------------------	//
//																		//
//	Gameplay every loop functions										//
//																		//
// --------------------------------------------------------------------	//

/*
**	Called every frame after the check for events and before the drawing;
*/

void	GamePlayController::Update()
{
	if (CurrentScene == MAIN_MENU)
	{
		if (ButtonPressed == true)
		{
			// transitionning to ingame;
			if (MainMenuBackground->Transform.Position.x < 1280.0)
			{
				MainMenuBackground->Transform.Position.x = Tools::LinearInterpolation(MainMenuBackground->Transform.Position.x, 1280.0, _lerpmu);
				_lerpmu += 0.005;
			}
			else
			{
				TransitionDone = true;
				_lerpmu = 0.0;
				CurrentScene = IN_GAME;
				ButtonPressed = false;
				std::cout << "Go to IN_GAME Scene" << std::endl;
			}
		}
	}
	else if (CurrentScene == IN_GAME)
	{
		// ----- On game start
		if (_onGameStartLaunched == false)
		{
			OnGameStart();
			_onGameStartLaunched = true;
		}
		World.UpdateWorld();
		Character.Update();

		// ----- Collision Event handling.
		if ((CollidingObject = CollisionController.PlayerCollides()))
		{
			HandleGameCollision();
		}
		if (Character.IsAlive)
		{
			GameDatas.Distance += World.WorldSpeed;
		}

		// ----- from death to MAIN_MENU
		if (Character.IsAlive == false && ButtonPressed == true)
		{
			// transitionning to main menu;
			if (MainMenuBackground->Transform.Position.x > 0.0)
			{
				MainMenuBackground->Transform.Position.x = Tools::LinearInterpolation(MainMenuBackground->Transform.Position.x, 0.0, _lerpmu);
				_lerpmu += 0.01;
			}
			else
			{
				TransitionDone = true;
				_lerpmu = 0.0;
				CurrentScene = MAIN_MENU;
				ButtonPressed = false;
				std::cout << "Go to MAIN_MENU Scene" << std::endl;

				ResetGame();
			}
		}
		GameModifier();
		UI.UpdateUIValues(GameDatas);
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

/*
**	What happens when the player collides with something.
*/

void	GamePlayController::HandleGameCollision()
{
	// std::cout << "COLLISION WITH " << CollidingObject->Name << std::endl;
	// ----- Character Collision
	if (CollidingObject->Name == "Coin" && CollidingObject->Visible == true)
	{
		GameDatas.PlayerCoins += 1;
		CollidingObject->Visible = false;
		CollidingObject->Transform.Position.z = -20.0; // make the coin disappear
			// Life Up
		if (GameDatas.PlayerCoins % 10 == 0)
		{
			GameDatas.PlayerLife += 1;
		}
	}
	else
	{
		// ----- Collision with obstacle
		if (Character.IsInvincible == false)
		{
			Character.SetInvincible();
			GameDatas.PlayerLife -= 1;
			if (GameDatas.PlayerLife <= 0)
			{
				std::cout << "Player dead!" << std::endl;
				World.Stop();
				Character.SetDead();
			}
		}
	}
}

// This method is STATIC -> glfw constraint.
// It forced me to make the GamePlayController a singleton instance...
void	GamePlayController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static GamePlayController	*GameInstance;

	GameInstance = &GamePlayController::Instance();

	if (GameInstance->CurrentScene == IN_GAME)
	{
		// ----- Character default events
		GameInstance->Character.HandleControls(window, key, scancode, action, mods);
		// ----- EVENTS DURING CHARACTER DEATH
		if (GameInstance->Character.IsAlive == false)
		{
			if (action == GLFW_PRESS)
			{
				GameInstance->ButtonPressed = true;
				GameInstance->UI.HideUI();
			}
		}
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
}

/*
**	Will modify the game values to set higher difficulty as time
**	goes by and also set the current score;
*/

void	GamePlayController::GameModifier()
{
	GameDatas.Score = (int)GameDatas.Distance + (100 * GameDatas.PlayerCoins);
	GameDatas.CurDistanceStep += World.WorldSpeed;
	if (GameDatas.Score >= GameDatas.DifficultyStep)
	{
		World.WorldSpeed += 0.08;
		GameDatas.CurDistanceStep = 0.0;
		GameDatas.DifficultyStep *= 2.0;
		if (World.TimeUntilSpawn > 1)
			World.TimeUntilSpawn -= 1; // one second less between spawns.
	}
	if (_spawnStep1 == false && GameDatas.Score > 2000)
	{
		World.NbSpawn += 1;
		_spawnStep1 = true;
	}
	if (_spawnStep2 == false && GameDatas.Score > 5000)
	{
		World.NbSpawn += 1;
		_spawnStep2 = true;
	}
	if (_spawnStep3 == false && GameDatas.Score > 8000)
	{
		World.NbSpawn += 1;
		_spawnStep3 = true;
	}
}

/*
**	Used to reset the game after the player died
**	and the UI screen hid everything.
*/

void	GamePlayController::ResetGame()
{
	World.ResetWorld();
	Character.ResetCharacter();
	GameDatas.PlayerLife = 3;
	GameDatas.PlayerCoins = 0;
	GameDatas.Score = 0;
	GameDatas.Distance = 0.0;
	GameDatas.CurDistanceStep = 0.0;
	GameDatas.DifficultyStep = 100;
	_spawnStep1 = false;
	_spawnStep2 = false;
	_spawnStep3 = false;
	_onGameStartLaunched = false;
}
