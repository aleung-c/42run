#ifndef CHARACTER_CONTROLLER_HPP
# define CHARACTER_CONTROLLER_HPP

class CharacterController
{
	public:
		CharacterController();
		~CharacterController();

		// Character
		GameObject	*Character;

		// Animation key frames
		GameObject	*Character_Idle;
		GameObject	*Character_Running1;
		GameObject	*Character_Running2;
		GameObject	*Character_Jumping;

		// Collider for gameplay purposes
		GameObject	*CharacterCollider;

		float		CharacterGroundHeight;

		// player move stats
		float		GravityForce;
		float		JumpForce;
		float		lerpMu;

		float		MoveSpeed;
		float		JumpMaxHeight;
		bool		IsOnGround;
		bool		MaxHeightReached;

		// key flags
		bool		MovingLeft;
		bool		MovingRight;
		bool		JumpPressed;
		bool		JumpUsed;

		bool		IsRunning;
		bool		IsJumping;

		void		InitCharacter(glm::vec3 Position);
		void		LoadCharacterAnimationsKeys();

		void		SetRunAnimation();
		void		SetJumpAnimation();

		void		HandleJump();
		void		HandleControls(GLFWwindow* window, int key, int scancode, int action, int mods);
		void		Update();
};

#endif