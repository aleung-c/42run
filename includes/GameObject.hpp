#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "QDrun.hpp"

class GameObject
{
	public:
		GameObject(std::string path);
		~GameObject();

		void	SetBuffers();
		void	DrawObject();
	
	private:
		GLuint							_vao;

		GLuint							_fvbo;
		GLuint							_vbo;
		GLuint							_nbo;
		//GLuint							_cbo;
		GLuint							_ubo;

		std::vector<glm::vec4>			_objFacesVertices;
		std::vector<glm::vec4>			_objVertices;
		std::vector<glm::vec3>			_objNormals;
		std::vector<glm::vec2>			_objUVs;
};

#endif
