#pragma once
class Material
{
public:
	Material();
	~Material();
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};

