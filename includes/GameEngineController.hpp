#ifndef GAMEENGINECONTROLLER_HPP
# define GAMEENGINECONTROLLER_HPP

# include "QDrun.hpp"

class GameEngineController
{
	public:
		GLFWwindow		*Window;


		std::vector<GameObject *>	GameObjectList;

		GameObject					*Character;

		GameEngineController();
		~GameEngineController();
	
		// class methods
		void			InitEngine();
		int				InitGLFW();
		int				InitOpenGL();
		void			LoadGameObjects();
		void			DrawObjects();
};

#endif
