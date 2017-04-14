#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "QDrun.hpp"

class GameObject
{
	public:
		GameObject(std::string objName);
		GameObject(std::string objName, std::string path);
		void	InitValues();
		void	GetObjValues(FILE *file);
		~GameObject();

		std::string						Name;

		glm::vec3						Position;
		glm::vec3						Rotation;
		glm::vec3						Scale;

		glm::vec3						BoundingBoxMin;
		glm::vec3						BoundingBoxMax;
		glm::vec3						BoundingBoxCenter;

		void	SetBuffers();
		void	DrawObject();
	
	private:
		bool							_hasModel;
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
