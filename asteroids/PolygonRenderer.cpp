#include "PolygonRenderer.h"

#include "Entity.h"
#include "Logger.h"

PolygonRenderer::PolygonRenderer(std::vector<Vec2> polygon,
								const GLchar* vertexShaderSource,
								const GLchar* fragmentShaderSource):RendererComponent(vertexShaderSource, fragmentShaderSource)
{
	_polygon = polygon;
}

PolygonRenderer::~PolygonRenderer()
{}

void PolygonRenderer::onAdd()
{
	RendererComponent::onAdd();

	std::vector<float> fQuadColor;

	// Setup color
	for (size_t i = 0; i < _polygon.size() * 3; i++)
	{
		fQuadColor.push_back(0.62f);
	}

	glGenBuffers(1, &_vertexBuffer); // And VBO	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _polygon.size() * sizeof(Vec2), &_polygon[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, fQuadColor.size() * sizeof(float), &fQuadColor[0], GL_STATIC_DRAW);
	_colorHandle = glGetAttribLocation(_shaderProgram.getProgramID(), "inColor");
}

void PolygonRenderer::onRemove()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_colorBuffer);
	RendererComponent::onRemove();
}

void PolygonRenderer::onFrame()
{
	_shaderProgram.useProgram(); 

	// Send our transformation to the currently bound shader
	Mat4 matrix = GetOwner().lock()->Transformation().GetMatrix();
	glUniformMatrix4fv(_matrixHandle, 1, GL_FALSE, &matrix[0][0]);
	//checkGlError("glUniformMatrix4fv");

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//checkGlError("glVertexAttribPointer");
	glEnableVertexAttribArray(mPositionHandle);	

	// 2nd attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glVertexAttribPointer(_colorHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//checkGlError("glVertexAttribPointer");
	glEnableVertexAttribArray(_colorHandle);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, _polygon.size());
	//checkGlError("glDrawArrays");
}
