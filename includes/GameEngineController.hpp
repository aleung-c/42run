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

		// matrix handling
		glm::mat4							MatIdentity;
		glm::mat4							MatTranslation;
		glm::mat4							MatScaling;

		glm::mat4							MatRotation;
		// float								matrix_x_rotation[4][4];
		// float								matrix_y_rotation[4][4];
		// float								matrix_z_rotation[4][4];

		glm::mat4							MatViewOrientation;
		glm::mat4							MatViewtTranslation;

		glm::mat4							MatPerspectiveProjection;
		glm::mat4							MatOrthographicProjection;

		GameEngineController();
		~GameEngineController();
	
		// class methods
		void			InitEngine();
		
		int				InitGLFW();
		int				InitOpenGL();

		void			LoadShaders();
		char			*GetFileContent(std::string file_path);

		void			LoadMatrices();

		void			LoadGameObjects();
		void			DrawObjects();
};

#endif
