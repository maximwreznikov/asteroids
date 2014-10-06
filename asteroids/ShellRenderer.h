#ifndef ShellRenderer_h
#define ShellRenderer_h

#include <vector>

#include "Math.h"
#include "RendererComponent.h"

/**
@brief Рендерер каркаса
@detailed Компонент отрисовывающий незакрашенный полигон
*/
class ShellRenderer : public RendererComponent
{
private:
	std::vector<Vec2>		_polygon;					/**< points of polygon */
	GLuint					_vertexBuffer;				/**< id of vertex buffer*/
public:
	ShellRenderer(const std::vector<Vec2>& polygon,
				 const GLchar* vertexShaderSource,
				 const GLchar* fragmentShaderSource);
	virtual ~ShellRenderer();

	virtual void onAdd();
	virtual void onRemove();
	virtual void onFrame();
};

#endif

