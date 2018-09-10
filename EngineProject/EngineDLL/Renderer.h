#pragma once
#include "Exports.h"
#include "Window.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Renderer
{
public:
	Renderer(Window* _window);
	~Renderer();
	bool Start();
	bool Stop();
	void SetClearColor(float r, float g, float b,float a);
	void ClearScreen();
	void SwapBuffers();
	unsigned int GenBuffer(float* buffer, int size);
	void DrawBuffer(unsigned int bufferID, int vtxCount);
	void DeleteBuffers(unsigned int _buffer);
private:
	Window* window;
	unsigned int vertexArrayID;
};

