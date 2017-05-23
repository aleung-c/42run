#ifndef CHARACTER_CONTROLLER_HPP
# define CHARACTER_CONTROLLER_HPP

class CharacterController
{
	public:
		CharacterController();
		~CharacterController();

		GameObject	*Character;

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

		void		InitCharacter(glm::vec3 Position);
		void		HandleJump();
		void		HandleControls(GLFWwindow* window, int key, int scancode, int action, int mods);
		void		Update();
};

#endif