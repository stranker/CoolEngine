#include "TextureImporter.h"
#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>

TextureImporter::BMPData TextureImporter::dataStruct;

unsigned int TextureImporter::loadBMP_custom(const char * imagepath){
		
	FILE * file = NULL;
	if (fopen_s(&file, imagepath, "rb") != 0) { printf("Image could not be opened\n"); return 0; }

	if (fread_s(dataStruct.header, sizeof(dataStruct.header), 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}
	if (dataStruct.header[0] != 'B' || dataStruct.header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	dataStruct.dataPos = *(int*)&(dataStruct.header[0x0A]);
	dataStruct.imageSize = *(int*)&(dataStruct.header[0x22]);
	dataStruct.width = *(int*)&(dataStruct.header[0x12]);
	dataStruct.height = *(int*)&(dataStruct.header[0x16]);

	// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
	if (dataStruct.imageSize == 0)    dataStruct.imageSize = dataStruct.width * dataStruct.height * 3; // 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (dataStruct.dataPos == 0)      dataStruct.dataPos = 54; // El encabezado del BMP está hecho de ésta manera

	if (dataStruct.data)
		delete dataStruct.data;
	dataStruct.data = new unsigned char[dataStruct.imageSize];

	fseek(file, dataStruct.dataPos, 0);

	// Leemos la información del archivo y la ponemos en el buffer
	fread(dataStruct.data, 1, dataStruct.imageSize, file);

	//Todo está en memoria ahora, así que podemos cerrar el archivo
	fclose(file);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	// Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar esta textura
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Se le pasa la imagen a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dataStruct.width, dataStruct.height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataStruct.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}
