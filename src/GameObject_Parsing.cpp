# include "../includes/QDrun.hpp"

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
			if (strncmp(lineHeader, "v", 3) == 0)
			{
				glm::vec4	vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertex.w = 1.0;
				// ----- Set Bounding box values;
				// Set x
				if (vertex.x > BoundingBoxMax.x)
					BoundingBoxMax.x = vertex.x;
				if (vertex.x < BoundingBoxMin.x)
					BoundingBoxMin.x = vertex.x;
				// Set y
				if (vertex.y > BoundingBoxMax.y)
					BoundingBoxMax.y = vertex.y;
				if (vertex.y < BoundingBoxMin.y)
					BoundingBoxMin.y = vertex.y;
				// Set z
				if (vertex.z > BoundingBoxMax.z)
					BoundingBoxMax.z = vertex.z;
				if (vertex.z < BoundingBoxMin.z)
					BoundingBoxMin.z = vertex.z;
				// ----- end set bounding box min max.
				_objVertices.push_back(vertex);
			}
			else if (strncmp(lineHeader, "vt", 3) == 0)
			{
				glm::vec2	uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y );
				_objUVs.push_back(uv);
			}
			else if (strncmp(lineHeader, "vn", 3) == 0)
			{
				glm::vec3	normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				_objNormals.push_back(normal);
			}
			else if (strncmp(lineHeader, "f", 3) == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1],
					&vertexIndex[2], &uvIndex[2], &normalIndex[2] );

				if (matches != 9)
				{
					printf("File can't be read by our simple parser :"
						"Try exporting with other options\n");
					return ;
				}
				_objVertexIndices.push_back(vertexIndex[0]);
				_objVertexIndices.push_back(vertexIndex[1]);
				_objVertexIndices.push_back(vertexIndex[2]);
				_objUVIndices.push_back(uvIndex[0]);
				_objUVIndices.push_back(uvIndex[1]);
				_objUVIndices.push_back(uvIndex[2]);
				_objNormalIndices.push_back(normalIndex[0]);
				_objNormalIndices.push_back(normalIndex[1]);
				_objNormalIndices.push_back(normalIndex[2]);
			}
		}
	}
}

int		GameObject::LoadTextureFile(t_bmp_texture *texture, std::string path)
{
	// Open the file
	FILE	*file;

	file = fopen(path.c_str(), "rb");
	if (!file)
	{
		std::cout << "Image could not be opened" << std::endl;
		return (-1);
	}
	if (fread(texture->header, 1, 54, file) != 54)
	{ // If not 54 bytes read == problem
    	std::cout << "Not a correct BMP file" << std::endl;
    	return (-1);
	}
	texture->data_pos = *(int*)&(texture->header[10]);
	texture->image_size = *(int*)&(texture->header[34]);
	texture->width = *(int*)&(texture->header[18]);
	texture->height = *(int*)&(texture->header[22]);
	if ( texture->header[0] != 'B' || texture->header[1] != 'M' )
	{
		std::cout << "Not a correct BMP file" << std::endl;
		return (-1);
	}
	// Debug print.
	//printf("default_texture infos:\nimage_size: %d \nwidth: %d \nheight: %d\n",
	//	texture->image_size, texture->width, texture->height);

	// Create a buffer
	texture->data = (unsigned char *)malloc(sizeof(unsigned char) * texture->image_size);
	// Read the actual data from the file into the buffer
	fread(texture->data, 1, texture->image_size, file);
	fclose(file);
	return (0);
}