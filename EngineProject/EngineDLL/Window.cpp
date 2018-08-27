#include "Window.h"


// Include GLFW
#include <GLFW\glfw3.h>

Window::Window(int _height, int _width, string &(_name)) :
	height(_height),
	width(_width)	
{	
	name = _name.c_str();
}

Window::~Window()
{
}

bool Window::Start() 
{	
	cout << "Window::Start()" << endl;
	if (!glfwInit())
	{
		fprintf(stderr, "Fallo al inicialiar GLFW\n");
		getchar();
		return false;
	}
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Fallo al crear Window\n");
		getchar();
		glfwTerminate();
		return false;
	}
	return true;
}
bool Window::Stop() 
{
	cout << "Window::Stop()" << endl;
	if (window != NULL)	
		glfwDestroyWindow((GLFWwindow*)window);

		window = NULL;
		glfwTerminate();	
	return true;
}
bool Window::ShouldClose()
{
	if (window)
	{
		return glfwWindowShouldClose((GLFWwindow*)window);
	}
		return true;	
}
void Window::PollEvents()
{
	glfwPollEvents();
}
