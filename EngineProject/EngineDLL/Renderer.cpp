#include "Renderer.h"
#include <GLFW\glfw3.h>


Renderer::Renderer(Window* _window) :
window(_window)
{	
}


Renderer::~Renderer()
{
}

bool Renderer::Start() const
{
	cout << "Renderer::Start()" << endl;	
	glfwMakeContextCurrent((GLFWwindow*)window);
	return true;
}
bool Renderer::Stop() const
{
	cout << "Renderer::Stop()" << endl;
	return true;
}
void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
void Renderer::ClearScreen()
{	
}
void Renderer::SwapBuffers() 
{
	glfwSwapBuffers((GLFWwindow*)window);
}
