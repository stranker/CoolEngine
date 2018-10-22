#pragma once
#include "Exports.h"
class ENGINEDLL_API TextureImporter
{
public:
	static unsigned int loadBMP_custom(const char * imagepath);
	struct BMPData {
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		unsigned int width, height;
		unsigned int imageSize;   // = width*height*3
								  // Información RGB
		unsigned char * data;
	};
	static BMPData dataStruct;
private:
};

