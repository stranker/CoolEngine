#pragma once
#include "Exports.h"
<<<<<<< HEAD
#include <glm\glm.hpp>
=======
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
class ENGINEDLL_API Material
{
	unsigned int programID;
	unsigned int matrixID;
public:
	Material();
	~Material();
<<<<<<< HEAD
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetMatrixProperty(const char*name, glm::mat4& mat);
=======
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);	
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
};

