#pragma once
#include "Exports.h"
#include "Window.h"
#include <glm\glm.hpp>
#include <glm\matrix.hpp>
#include <iostream>
using namespace std;
class ENGINEDLL_API Renderer
{
private:
	Window* window;
	unsigned int vertexArrayID;	
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 MVP;
	void UpdateMVP();
public:
	enum DrawTypes {GL_TRIANGLES = 0x0004, 
		GL_TRIANGLE_STRIP = 0x0005,
		GL_TRIANGLE_FAN = 0x0006};
	Renderer(Window* _window);
	~Renderer();
	bool Start();
	bool Stop();
	void SetClearColor(float r, float g, float b,float a);
	void ClearScreen();
	void SwapBuffers();
	unsigned int GenBuffer(float* buffer, int size);	
	void DrawBuffer(unsigned int bufferID, int vtxCount, int enableVertexIndex, DrawTypes typeOfDraw);
	void EnableBuffer(int enableIndex);
	void DeleteBuffers(unsigned int _buffer);
	void BindMaterial(unsigned int programID);
	void LoadIdentityMatrix();
	void SetModelMatrix(glm::mat4 mat);
	void MultiplyModelMatrix(glm::mat4 mat);
	glm::mat4& GetMVP() { return MVP; }
};

