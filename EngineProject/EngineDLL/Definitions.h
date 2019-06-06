#pragma once


struct ModelData
{
	std::vector<float> position;
	std::vector<float> uv;
	std::vector<unsigned int> indexes;
	unsigned int bufferVertex;
	unsigned int bufferUV;
	unsigned int bufferIndex;
};