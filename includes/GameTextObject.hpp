#ifndef GAMETEXTOBJECT_HPP
# define GAMETEXTOBJECT_HPP

# include "QDrun.hpp"

class GameTextObject
{
	public:
		GameTextObject(std::string text);
		~GameTextObject();

		std::string						Text;
		glm::vec3						Color;

		glm::vec3						Position;
		GLfloat							Scale;

		void							InitValues();
		void							SetBuffers();
		GLuint							GetVao();
		GLuint							GetVbo();

	private:
		GLuint							_vao;
		GLuint							_vbo;

};

#endif
