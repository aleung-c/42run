#ifndef GAMEENGINECONTROLLER_HPP
# define GAMEENGINECONTROLLER_HPP

# include "QDrun.hpp"

/*
**	This engine is a GameObject collector. When a new GameObject
**	is created, it goes into the engine's list of object,
**	and this engine will draw it automatically, applying matrices
**	and stuff.
*/

class GameEngineController
{
	public:
		// this is a singleton
		static GameEngineController&	Instance();

		GLFWwindow		*Window;


		std::vector<GameObject *>	GameObjectList;

		GameObject					*MainCamera;

		char						*VertexShader_1;
		char						*FragmentShader_1;
		GLuint						MainShaderProgramme;

		// matrix handling
		// model
		glm::mat4							BaseMatModelIdentity;
		glm::mat4							BaseMatModelTranslation;
		glm::mat4							BaseMatModelRotation;
		glm::mat4							BaseMatModelScaling;

		glm::mat4							MatModelIdentity;
		glm::mat4							MatModelTranslation;
		glm::mat4							MatModelRotation;
		glm::mat4							MatModelScaling;
		// float								matrix_x_rotation[4][4];
		// float								matrix_y_rotation[4][4];
		// float								matrix_z_rotation[4][4];

		// view -> camera
		float								CameraNear;
		float								CameraFar;
		float								CameraFov;
		float								CameraAspect;

		// projection -> persp or ortho
		glm::mat4							MatPerspectiveProjection;
		glm::mat4							MatOrthographicProjection;

		glm::mat4							MatModel;
		glm::mat4							MatView;

		glm::mat4							MatMVP;

		GameEngineController();
		~GameEngineController();
	
		// class methods
		void			InitEngine();
		
		int				InitGLFW();
		int				InitOpenGL();

		void			LoadShaders();
		char			*GetFileContent(std::string file_path);

		void			LoadMatrices();

		void			ApplyMatricesToObject(GameObject *Object);
		void			DrawObjects();

	private:
		static GameEngineController m_instance;
};

#endif
