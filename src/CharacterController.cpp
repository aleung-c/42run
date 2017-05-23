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
{
	MoveSpeed = 0.2;
	GravityForce = 0.35;
	JumpForce = 0.4;
	JumpMaxHeight = 4.0;
	IsOnGround = true;
	lerpMu = 0.0;
	CharacterGroundHeight = 0.4;
}

CharacterController::~CharacterController()
{

}

void	CharacterController::InitCharacter(glm::vec3 Position)
{
	Character = new GameObject("Character", "./ressources/models/character_idle.obj");
	Character->Position.x = Position.x;
	Character->Position.y = CharacterGroundHeight;
	Character->Position.z = Position.z;

}

void	CharacterController::Update()
{
	Character->Rotation.y += 2;
	if (MovingLeft == true)
	{
		Character->Position.x += MoveSpeed;
	}
	else if (MovingRight == true)
	{
		Character->Position.x -= MoveSpeed;
	}
	// jump is special, as releasing in mid air makes the player fall down.
	HandleJump();
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
	if (Character->Position.y <= CharacterGroundHeight)
	{
		IsOnGround = true;
		MaxHeightReached = false;
		lerpMu = 0.0;
	}
	else
	{
		IsOnGround = false;
	}

	// when space pressed
	if (JumpPressed)
	{
		if (MaxHeightReached == false && JumpUsed == false)
		{
			lerpMu += 0.05;
			//Character->Position.y += JumpForce;
			Character->Position.y = Tools::LinearInterpolation(Character->Position.y, JumpMaxHeight, lerpMu);
			
			if (Character->Position.y >= JumpMaxHeight - 0.02)
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
				if (Character->Position.y - GravityForce < CharacterGroundHeight)
					Character->Position.y = CharacterGroundHeight;
				else
					Character->Position.y -= GravityForce;
			}
		}
	}
	else
	{
		// gravity pulling down.
		if (Character->Position.y - GravityForce < CharacterGroundHeight)
			Character->Position.y = CharacterGroundHeight;
		else
			Character->Position.y -= GravityForce;
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
