#ifndef RenderComponent_h
#define RenderComponent_h

#include <GLES2/gl2.h>

#include "EntityComponent.h"
#include "GLShaders.h"

class RendererComponent;
typedef std::shared_ptr<RendererComponent> HandleRenderer;

/**
@brief Базовый компонент для отрисовки объекта
@detailed Регистрируется в графическом движке, инициализирует шейдеры, 
достает из них id разнах аттрибутов
*/
class RendererComponent :public EntityComponent, public std::enable_shared_from_this<RendererComponent>
{
protected:
	//variables for opengl 
	const GLchar*		_vertexShaderSource;		/**< source for vertex shader */
	const GLchar*		_fragmentShaderSource;		/**< source for fragment shader */

	GLuint				_matrixHandle;				/**< id of matrix */

	GLShader			_vertexShader;
	GLShader			_fragmentShader;
	GLShaderProgram		_shaderProgram;				/**< shader program for render */

	GLuint				mPositionHandle;			/**< id of position attribute in vertex buffer*/
public:
	RendererComponent(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
	virtual ~RendererComponent();

	virtual void onAdd();
	virtual void onRemove();
	virtual void onFrame() = 0;
	
	virtual void RegisterComponent(Owner entity) final;
	virtual void UnregisterComponent() final;
};

#endif

