#include "RendererComponent.h"

#include <GLES2/gl2ext.h>
#include <stdexcept>

#include "Logger.h"
#include "Engine.h"
#include "Entity.h"
#include "RenderManager.h"

RendererComponent::RendererComponent(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
{
	_vertexShaderSource = vertexShaderSource;
	_fragmentShaderSource = fragmentShaderSource;
}


RendererComponent::~RendererComponent()
{
}

void RendererComponent::onAdd()
{
	// Load shaders and create shader program
	_vertexShader.loadShader(_vertexShaderSource, GL_VERTEX_SHADER);
	_fragmentShader.loadShader(_fragmentShaderSource, GL_FRAGMENT_SHADER);

	if (!_vertexShader.isLoaded())
		throw std::runtime_error(std::string("Can`t compile vertex shader"));

	if (!_fragmentShader.isLoaded())
		throw std::runtime_error(std::string("Can`t compile fragment shader"));

	_shaderProgram.createProgram();
	_shaderProgram.addShaderToProgram(&_vertexShader);
	_shaderProgram.addShaderToProgram(&_fragmentShader);

	_shaderProgram.linkProgram();

	// Get handle of mvp matrix to set location and roatation
	_matrixHandle = glGetUniformLocation(_shaderProgram.getProgramID(), "MVP");

	mPositionHandle = glGetAttribLocation(_shaderProgram.getProgramID(), "inPosition");
}

void RendererComponent::onRemove()
{
	_shaderProgram.deleteProgram();
	_vertexShader.deleteShader();
	_fragmentShader.deleteShader();
}

void RendererComponent::UnregisterComponent()
{
	EntityComponent::UnregisterComponent();
	Engine::Instance()->GetRenderer()->DetachComponent(GetOwner().lock(), shared_from_this());
}

void RendererComponent::RegisterComponent(Owner entity)
{
	EntityComponent::RegisterComponent(entity);
	Engine::Instance()->GetRenderer()->AttachComponent(entity.lock(), shared_from_this());
}