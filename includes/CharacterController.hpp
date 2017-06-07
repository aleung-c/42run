#ifndef CHARACTER_CONTROLLER_HPP
# define CHARACTER_CONTROLLER_HPP

class CharacterController
{
	public:
		CharacterController();
		~CharacterController();

		// Other controller access attachment
		WorldController	*WorldController;

		// Character
		GameObject	*Character;

		// Animation key frames
		GameObject	*Character_Idle;
		GameObject	*Character_Dead;
		GameObject	*Character_Running1;
		GameObject	*Character_Running2;
		GameObject	*Character_Jumping;

		// Collider for gameplay purposes
		GameObject	*CharacterCollider;

		bool		IsAlive;

		float		CharacterGroundHeight;

		// player move stats
		float		GravityForce;
		float		JumpForce;
		float		lerpMu;

		float		MoveSpeed;
		float		JumpMaxHeight;
		bool		IsOnGround;
		bool		MaxHeightReached;

		float		PlayerWallsOffset;

		// key flags
		bool		MovingLeft;
		bool		MovingRight;
		bool		JumpPressed;
		bool		JumpUsed;

		bool		IsRunning;
		bool		IsJumping;

		bool		IsInvincible;
		std::chrono::time_point<std::chrono::system_clock>	StartInvincibility;
		int			InvincibilityTime;
		int			ElapsedSeconds;
		int			FrameCounter;

		void		InitCharacter(glm::vec3 Position);
		void		LoadCharacterAnimationsKeys();

		void		SetRunAnimation();
		void		SetJumpAnimation();
		void		SetIdleAnimation();
		void		SetDeadAnimation();

		void		HandleMoving();
		void		HandleJump();
		void		HandleControls(GLFWwindow* window, int key, int scancode, int action, int mods);
		void		Update();

		void		HandleInvincibility();
		void		SetInvincible();
		void		SetDead();

		void		ResetCharacter();
};

#endif