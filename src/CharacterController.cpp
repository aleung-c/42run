# include "../includes/QDrun.hpp"

// --------------------------------------------------------------------	//
//																		//
//	Character control and access class									//
//																		//
// --------------------------------------------------------------------	//

/*
**	This is the class where ill handle every character related actions,
**	such as the jumping, strafing, skills, etc etc.
*/

CharacterController::CharacterController()
:
	GravityForce(DEFAULT_GRAVITY_FORCE),
	JumpForce(DEFAULT_JUMP_FORCE),
	MoveSpeed(DEFAULT_MOVE_SPEED),
	JumpMaxHeight(DEFAULT_JUMP_MAX_HEIGHT),
	PlayerWallsOffset(DEFAULT_PLAYER_WALLS_OFFSET)
{
	// GravityForce = 0.35;
	// JumpForce = 0.4;
	// MoveSpeed = 0.2;
	// JumpMaxHeight = 4.0;
	IsOnGround = true;
	lerpMu = 0.0;
	CharacterGroundHeight = 2.5;
}

CharacterController::~CharacterController()
{

}

void	CharacterController::InitCharacter(glm::vec3 Position)
{
	WorldController = &(GamePlayController::Instance().World);

	Character = new GameObject("Character", "./ressources/models/character_idle.obj");
	Character->Transform.Position.x = Position.x;
	Character->Transform.Position.y = CharacterGroundHeight;
	Character->Transform.Position.z = Position.z;

	// reajust max jump height from char vertical position.
	JumpMaxHeight += Character->Transform.Position.y;

	LoadCharacterAnimationsKeys();

	CharacterCollider = new GameObject("CharacterCollider", "./ressources/models/character_collision_box.obj");
	CharacterCollider->Transform.Position = Character->Transform.Position;

	// GameUIObject *UItest = new GameUIObject("UI test", "./ressources/UI_Elem_1.bmp");
	// if (UItest)
	// {
	// }
}

/*
**	Here, we will load each 3d model and texture for the character's different
**	Key animations frames, to make the morph targets.
*/

void	CharacterController::LoadCharacterAnimationsKeys()
{
	Character_Idle = new GameObject("Character", "./ressources/models/character_idle.obj");
	Character_Running1 = new GameObject("Character_key", "./ressources/models/character_running_1.obj");
	Character_Running2 = new GameObject("Character_key", "./ressources/models/character_running_2.obj");
	Character_Jumping = new GameObject("Character_key", "./ressources/models/character_jumping.obj");
	Character_Idle->Visible = false;
	Character_Running1->Visible = false;
	Character_Running2->Visible = false;
	Character_Jumping->Visible = false;

	Character->MorphAnimation.SetSpeed(0.2);
	// SetRunAnimation();
	// Character->MorphAnimation.Start();
}

void	CharacterController::SetRunAnimation()
{
	// basic run animation.
	Character->MorphAnimation.Stop();
	Character->MorphAnimation.ClearFrames();
	Character->MorphAnimation.SetRepeat(true);
	Character->MorphAnimation.SetSpeed(0.2);
	Character->MorphAnimation.AddKeyFrame(Character_Running1);
	Character->MorphAnimation.AddKeyFrame(Character);
	Character->MorphAnimation.AddKeyFrame(Character_Running2);
	Character->MorphAnimation.AddKeyFrame(Character);
	Character->MorphAnimation.Start();
}

void	CharacterController::SetJumpAnimation()
{
	// basic run animation.
	Character->MorphAnimation.Stop();
	Character->MorphAnimation.ClearFrames();
	Character->MorphAnimation.SetRepeat(false);
	Character->MorphAnimation.SetSpeed(0.07);
	Character->MorphAnimation.SetStayOnEnd(true);
	Character->MorphAnimation.CurFrame = Character_Idle;
	Character->MorphAnimation.AddKeyFrame(Character_Jumping);
	Character->MorphAnimation.Start();
}

/*
**	Called at each frame.
*/

void	CharacterController::Update()
{
	HandleMoving();
	HandleJump();
	CharacterCollider->Transform.Position = Character->Transform.Position;
}

void	CharacterController::HandleMoving()
{
	if (MovingLeft == true)
	{
		if (Character->Transform.Position.x
			< (WorldController->GameSpaceMax_X - PlayerWallsOffset))
		{
			Character->Transform.Position.x += MoveSpeed;
		}
	}
	else if (MovingRight == true)
	{
		if (Character->Transform.Position.x
			> (WorldController->GameSpaceMin_X + PlayerWallsOffset))
		{
		Character->Transform.Position.x -= MoveSpeed;
		}
	}
}

/*
**	Note: In my view, jumping in video game is always a sensitive matter.
**	Indeed, just adding or taking vertical force gives a bad looking jump.
**	It has to be interpolated, multi checked with the "ground touching" problem,
**	to have a real jump, or at least a not too bad jump.
*/

void	CharacterController::HandleJump()
{
	// on ground touched.
	if (Character->Transform.Position.y <= CharacterGroundHeight)
	{
		IsOnGround = true;
		MaxHeightReached = false;
		lerpMu = 0.0;
		// change animation state.
		if (!IsRunning)
		{
			IsJumping = false;
			IsRunning = true;
			SetRunAnimation();
		}
	}
	else
	{
		IsOnGround = false;
	}

	// when space pressed
	if (JumpPressed && JumpUsed == false)
	{
		// change animation state.
		if (!IsJumping)
		{
			IsRunning = false;
			IsJumping = true;
			SetJumpAnimation();
		}

		if (MaxHeightReached == false && JumpUsed == false)
		{
			// JUMP FORCE UP
			lerpMu += 0.05;
			Character->Transform.Position.y
				= Tools::LinearInterpolation(Character->Transform.Position.y, JumpMaxHeight, lerpMu);

			// check if max height reached.
			if (Character->Transform.Position.y >= JumpMaxHeight)
			{
				MaxHeightReached = true;
				JumpUsed = true;
			}
		}
		else
		{
			if (IsOnGround == false)
			{
				// gravity pulling down.
				if (Character->Transform.Position.y - GravityForce < CharacterGroundHeight)
					Character->Transform.Position.y = CharacterGroundHeight;
				else
					Character->Transform.Position.y -= GravityForce;
			}
		}
	}
	else
	{
		// by default, gravity pulling down.
		if (Character->Transform.Position.y - GravityForce < CharacterGroundHeight)
			Character->Transform.Position.y = CharacterGroundHeight;
		else
			Character->Transform.Position.y -= GravityForce;
	}
}

void	CharacterController::HandleControls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT)
		{
			MovingLeft = true;
		}
		else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT)
		{
			MovingRight = true;
		}
		else if (key == GLFW_KEY_SPACE)
		{
			JumpPressed = true;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT)
		{
			MovingLeft = false;
		}
		else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT)
		{
			MovingRight = false;
		}
		else if (key == GLFW_KEY_SPACE)
		{
			JumpPressed = false;
			JumpUsed = false;
		}
	}
}
