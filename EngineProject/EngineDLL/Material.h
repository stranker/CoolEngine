#pragma once
#include "Exports.h"
#include <glm\glm.hpp>
class ENGINEDLL_API Material
{
	unsigned int programID;
	unsigned int matrixID;
public:
	Material();
	~Material();
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetMatrixProperty(const char*name, glm::mat4& mat);
};

