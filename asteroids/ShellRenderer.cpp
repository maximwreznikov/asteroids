#include "ShellRenderer.h"

#include "Entity.h"
#include "shaders.h"

ShellRenderer::ShellRenderer(const std::vector<Vec2>& polygon,
							const GLchar* vertexShaderSource,
							const GLchar* fragmentShaderSource) :RendererComponent(vertexShaderSource, fragmentShaderSource)
{
	_polygon = polygon;
}


ShellRenderer::~ShellRenderer()
{
}

void ShellRenderer::onAdd()
{
	RendererComponent::onAdd();
	
	int svec2 = sizeof(Vec2);
	int sf = sizeof(float);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _polygon.size() * sizeof(Vec2), &_polygon[0], GL_STATIC_DRAW);
}

void ShellRenderer::onRemove()
{
	glDeleteBuffers(1, &_vertexBuffer);
	RendererComponent::onRemove();
}

void ShellRenderer::onFrame()
{
	_shaderProgram.useProgram();

	// Send our transformation to the currently bound shader
	Mat4 matrix = GetOwner().lock()->Transformation().GetMatrix();
	glUniformMatrix4fv(_matrixHandle, 1, GL_FALSE, &matrix[0][0]);

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(mPositionHandle);

	glDrawArrays(GL_LINE_LOOP, 0, _polygon.size());
}

