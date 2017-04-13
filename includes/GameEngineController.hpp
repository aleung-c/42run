#ifndef GAMEENGINECONTROLLER_HPP
# define GAMEENGINECONTROLLER_HPP

# include "QDrun.hpp"

class GameEngineController
{
	public:
		GLFWwindow		*Window;


		std::vector<GameObject *>	GameObjectList;

		GameObject					*Character;
		GameObject					*Cube;

		char						*VertexShader_1;
		char						*FragmentShader_1;
		GLuint						MainShaderProgramme;

		glm::mat4					MatIdentity;

		GameEngineController();
		~GameEngineController();
	
		// class methods
		void			InitEngine();
		
		int				InitGLFW();
		int				InitOpenGL();

		void			LoadShaders();
		char			*GetFileContent(std::string file_path);

		void			LoadGameObjects();
		void			DrawObjects();
};

#endif
