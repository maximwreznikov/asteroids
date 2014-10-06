#include "BulletRenderer.h"

#include "Math.h"

#include "Entity.h"
#include "shaders.h"


BulletRenderer::BulletRenderer():RendererComponent(glPointVertex, glPointFragment)
{
}


BulletRenderer::~BulletRenderer()
{
}

void BulletRenderer::onAdd()
{
	RendererComponent::onAdd();

	float mWidth = 1.0;
	float mHeight = 1.0;

	float points[] = {
		0.0f, 0.0f, 0.0f
	};

	glGenBuffers(1, &_positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);	

	//float pos[] = {
	//	-0.5, -0.5,
	//	-0.5, 0.5,
	//	0.5, 0.5,
	//	0.5, -0.5,
	//};

	//glGenBuffers(1, &_textureBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, _textureBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_DYNAMIC_DRAW);

	//_textureHandle = glGetAttribLocation(_shaderProgram.getProgramID(), "textureUv");
}

void BulletRenderer::onRemove()
{
	glDeleteBuffers(1, &_positionBuffer);
	//glDeleteBuffers(1, &_textureBuffer);
	RendererComponent::onRemove();
}

#include "Logger.h"
#include <iostream>
void BulletRenderer::onFrame()
{
	_shaderProgram.useProgram();

	// Send our transformation to the currently bound shader
	Mat4 matrix = GetOwner().lock()->Transformation().GetMatrix();
	glUniformMatrix4fv(_matrixHandle, 1, GL_FALSE, &matrix[0][0]);
	//checkGlError("glUniformMatrix4fv");

	glBindBuffer(GL_ARRAY_BUFFER, _positionBuffer);
	glEnableVertexAttribArray(mPositionHandle);
	glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, _textureBuffer);
	//glEnableVertexAttribArray(_textureHandle);
	//glVertexAttribPointer(_textureHandle, 2, GL_FLOAT, GL_FALSE, 0, 0);	

	glDrawArrays(GL_POINTS, 0, 1);
	//checkGlError("glDrawArrays");
}
