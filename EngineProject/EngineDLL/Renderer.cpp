#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
Renderer::Renderer(Window* _window) :
	window(_window)
{	
}


Renderer::~Renderer()
{
}

bool Renderer::Start()
{
	cout << "Renderer::Start()" << endl;
	if (window)
	{
		glfwMakeContextCurrent((GLFWwindow*)window->GetWindowPrt());		
		if (!glewInit())
		{
			glGenVertexArrays(1, (&vertexArrayID));
			glBindVertexArray(vertexArrayID);
			return true;
		}
	}
}
bool Renderer::Stop()
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
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::SwapBuffers() 
{
	glfwSwapBuffers((GLFWwindow*)window->GetWindowPrt());
}
unsigned int Renderer::GenBuffer(float* buffer, int size)
{	
	unsigned int vertexbuffer;
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	return vertexbuffer;
}
void Renderer::DrawBuffer(unsigned int bufferID, int vtxCount)
{
	// 1rst attribute buffer : vértices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
	// Dibujar el triángulo !
	glDrawArrays(GL_TRIANGLES, 0, vtxCount); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
	glDisableVertexAttribArray(0);
}
void Renderer::DeleteBuffers(unsigned int _buffer)
{
	glDeleteBuffers(1, &_buffer);
}