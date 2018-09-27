#pragma once
#include "Exports.h"
#include "Window.h"
<<<<<<< HEAD
#include <glm\glm.hpp>
#include <glm\matrix.hpp>
=======
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
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
	Renderer(Window* _window);
	~Renderer();
	bool Start();
	bool Stop();
	void SetClearColor(float r, float g, float b,float a);
	void ClearScreen();
	void SwapBuffers();
<<<<<<< HEAD
	unsigned int GenBuffer(float* buffer, int size);	
	void DrawBuffer(unsigned int bufferID, int vtxCount, int enableVertexIndex);
	void DeleteBuffers(unsigned int _buffer);
	void BindMaterial(unsigned int programID);
	void LoadIdentityMatrix();
	void SetModelMatrix(glm::mat4 mat);
	void MultiplyModelMatrix(glm::mat4 mat);
	glm::mat4& GetMVP() { return MVP; }
=======
	unsigned int GenBuffer(float* buffer, int size);
	void DrawBuffer(unsigned int bufferID, int vtxCount);
	void DeleteBuffers(unsigned int _buffer);
	void BindMaterial(unsigned int programID);
private:
	Window* window;
	unsigned int vertexArrayID;
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
};

