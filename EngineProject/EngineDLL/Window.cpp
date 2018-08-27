#include "Window.h"



Window::Window(int _height, int _width, string &(_name)) :
	height(_height),
	width(_width)
{	
	name = _name.c_str();
}

Window::~Window()
{
}

bool Window::Start() const
{
	cout << "Window::Start()" << endl;
	return true;
}
bool Window::Stop() const
{
	cout << "Window::Stop()" << endl;
	return true;
}
