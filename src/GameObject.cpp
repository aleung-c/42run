# include "../includes/QDrun.hpp"

// --------------------------------------------------------------------	//
//																		//
//	This is the class for and object in the game						//
//	An object can OR NOT have a model. If it does, it is loaded			//
//	Every object has a NAME, it will be useful to search through them.	//
//	Also, every object has some variables such as position, rotation,	//
//	etc etc ...															//
//																		//
// --------------------------------------------------------------------	//

/*
**	The constructor for an object without a model.
**	We can imagine the camera for example, or a simple point in world space.
*/

GameObject::GameObject(std::string objName)
{
	_hasModel = false;
	Name = objName;
	InitValues();
	GameEngineController::Instance().GameObjectList.push_back(this);
}

/*
**	The constructor for an object with a model.
**	This will load the buffers required, and allow this object
**	to be "drawn" by the engine.
*/

GameObject::GameObject(std::string objName, std::string path)
{
	FILE * file;

	file = fopen(path.c_str(), "r");
	if (file == NULL)
	{
		std::cout << "Impossible to open the file !" << std::endl;
		return ;
	}
	Name = objName;
	_hasModel = true;
	InitValues();
	GetObjValues(file);
	SetBuffers();
	GameEngineController::Instance().GameObjectList.push_back(this);
}

void		GameObject::InitValues()
{
	Position = glm::vec3(0.0, 0.0, 0.0);
	// for now, we will imagine euleur rotations.
	Rotation = glm::vec3(0.0, 0.0, 0.0);
	Scale = glm::vec3(1.0, 1.0, 1.0);

	BoundingBoxMin = glm::vec3(0.0, 0.0, 0.0);
	BoundingBoxMax = glm::vec3(0.0, 0.0, 0.0);
	BoundingBoxCenter = glm::vec3(0.0, 0.0, 0.0);
}

/*
** The loader for our obj files.
*/

void		GameObject::GetObjValues(FILE *file)
{
	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break ;
		else
		{
			if (strncmp(lineHeader, "v", 10) == 0)
			{
				glm::vec4	vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertex.w = 0.0;
				_objVertices.push_back(vertex);
				//printf("%f %f %f %f\n", vertex.x, vertex.y, vertex.z, vertex.w);
			}
			else if (strncmp(lineHeader, "vt", 10) == 0)
			{
				glm::vec2	uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y );
				_objUVs.push_back(uv);
			}
			else if (strcmp( lineHeader, "vn") == 0)
			{
				glm::vec3	normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				_objNormals.push_back(normal);
			}
			// else if ( strcmp( lineHeader, "f" ) == 0 )
			// {
			// 	std::string		vertex1, vertex2, vertex3;
			// 	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			// 	int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			// 	if (matches != 9){
			// 		printf("File can't be read by our simple parser : ( Try exporting with other options\n");
			// 		return false;
			// 	}
			// 	vertexIndices.push_back(vertexIndex[0]);
			// 	vertexIndices.push_back(vertexIndex[1]);
			// 	vertexIndices.push_back(vertexIndex[2]);
			// 	uvIndices.push_back(uvIndex[0]);
			// 	uvIndices.push_back(uvIndex[1]);
			// 	uvIndices.push_back(uvIndex[2]);
			// 	normalIndices.push_back(normalIndex[0]);
			// 	normalIndices.push_back(normalIndex[1]);
			// 	normalIndices.push_back(normalIndex[2]);
			// }
		}
	}
}

GameObject::~GameObject()
{

}

void		GameObject::SetBuffers()
{
	// -------------------------------------------------------------------------- //
	//	VAO - Vertex Array object												  //
	// -------------------------------------------------------------------------- //
	_vao = 0;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// -------------------------------------------------------------------------- //
	//	VBOs - Vertex buffer object												  //
	// -------------------------------------------------------------------------- //

	// generating buffer of face vertices.
	_fvbo = 0;
	glGenBuffers(1, &(_fvbo));

	glBindBuffer(GL_ARRAY_BUFFER, _fvbo);
	glBufferData(GL_ARRAY_BUFFER, _objFacesVertices.size() * sizeof(glm::vec4), &_objFacesVertices[0],
					GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// generating vbo buffers
	std::cout << "vertices nb : " << _objVertices.size() << std::endl;
	_vbo = 0;
	glGenBuffers(1, &(_vbo));

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _objVertices.size() * sizeof(glm::vec4), &_objVertices[0],
					GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// for the normals
	_nbo = 0;
	glGenBuffers(1, &(_nbo));

	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
	glBufferData(GL_ARRAY_BUFFER, _objNormals.size() * sizeof(glm::vec3), &_objNormals[0],
					GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);
	
	// the color buffer cbo.
	// sc->cbo = 0;
	// glGenBuffers(1, &(_cbo));

	// glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((sc->total_faces * 3) * 3), sc->vertex_color_values, GL_STATIC_DRAW);
	// glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// glEnableVertexAttribArray(2);

	// the uv buffer.
	_ubo = 0;
	glGenBuffers(1, &(_ubo));

	glBindBuffer(GL_ARRAY_BUFFER, _ubo);
	glBufferData(GL_ARRAY_BUFFER, _objUVs.size() * sizeof(glm::vec2), &_objUVs[0],
					GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);
}

void		GameObject::DrawObject()
{
	//std::cout << "vertices nb : " << _objVertices.size() << std::endl;
	// glEnableVertexAttribArray(1);
	// glEnableVertexAttribArray(2);
	// glEnableVertexAttribArray(3);
	if (_hasModel == true)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glDrawArrays (GL_POINTS, 0, _objVertices.size());

		glDisableVertexAttribArray(0);
		// glDisableVertexAttribArray(1);
		// glDisableVertexAttribArray(2);
		// glDisableVertexAttribArray(3);
	}
}