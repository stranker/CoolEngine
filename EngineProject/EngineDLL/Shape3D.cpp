#include "Shape3D.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


Shape3D::Shape3D(Renderer* _renderer, string modelPath) :
	Entity(_renderer)
{
	std::vector<ModelData> models = ModelImporter::LoadMesh(modelPath);
	mesh = models[0];
			
	shouldDispose = false;	
	SetVertices(&mesh.position[0], mesh.position.size());
	SetIndexes(&mesh.indexes[0], mesh.indexes.size());
	verticesUVArray = &mesh.uv[0];
	vtxUvCount = mesh.uv.size();
}
Shape3D::~Shape3D()
{
	Dispose();
}
void Shape3D::SetVertices(float* _vertices, int count)
{
	Dispose();
	vertices = _vertices;
	vtxCount = count;
	shouldDispose = true;
	bufferData = (renderer->GenBuffer(vertices, vtxCount * sizeof(float)));
}
void Shape3D::SetTexture(const char * imagepath)
{
	texture = TextureImporter::loadBMP_custom(imagepath);
	heightTotal = TextureImporter::dataStruct.height;
	widthTotal = TextureImporter::dataStruct.width;
	SetVerticesUV(verticesUVArray);
}
void Shape3D::SetVerticesUV(float* vertices)
{
	verticesUV = (renderer->GenBuffer(vertices, vtxUvCount * sizeof(float)));
}
void Shape3D::SetIndexes(unsigned int* _indexes, int count)
{	
	indexes = _indexes;	
	indexCount = count;
	bufferIndex = (renderer->GenBufferIndex(indexes, indexCount * sizeof(unsigned int) ));
}
void Shape3D::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());		
		material->SetTextureProperty("myTextureSampler", texture);;
	}
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	renderer->BindBuffer(bufferData, 3, 0);
	renderer->BindBuffer(verticesUV, 2, 1);
	renderer->DrawIndex(indexCount);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}
void Shape3D::Dispose()
{
	if (shouldDispose)
	{
		renderer->DeleteBuffers(bufferData);
		renderer->DeleteBuffers(verticesUV);
		/*if (vertices)
		{
		delete[] vertices;
		vertices = NULL;
		}*/
		shouldDispose = false;
	}
}
void Shape3D::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
void Shape3D::BindMaterial()
{
	renderer->BindMaterial(programID);
}
void Shape3D::SetPosition(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape3D::MoveIn(float x, float y, float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape3D::SetScale(float x, float y, float z)
{
	scl[0] = x;
	scl[1] = y;
	scl[2] = z;

	scale = glm::scale(glm::mat4(1.0f), scl);
	UpdateModelMatrix();
}
void Shape3D::SetRotateX(float x)
{
	rot[0] = x;
	glm::vec3 axis;
	axis[0] = x;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	UpdateModelMatrix();
}
void Shape3D::SetRotateY(float y)
{
	rot[1] = y;
	glm::vec3 axis;
	axis[1] = y;
	axis[0] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), y, axis);
	UpdateModelMatrix();
}
void Shape3D::SetRotateZ(float z)
{
	rot[2] = z;
	glm::vec3 axis;
	axis[2] = z;
	axis[0] = axis[1] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), z, axis);
	UpdateModelMatrix();
}
void Shape3D::UpdateModelMatrix()
{
	model = translate * rotateX * rotateY * rotateZ * scale;
}
