#ifndef PolygonRenderer_h
#define PolygonRenderer_h

#include <vector>
#include <GLES2/gl2.h>

#include "Math.h"
#include "RendererComponent.h"

/**
@brief –ендерер полигона
@detailed  омпонент отрисовывающий закрашенный полигон
*/
class PolygonRenderer : public RendererComponent
{
private:
	std::vector<Vec2> _polygon;		/**< локальные координаты вершин полигона*/

	//opengl variables
	GLuint	_vertexBuffer;			/**< id of vertex buffer*/

	GLuint  _colorBuffer;			/**< id of color buffer*/	
	GLuint  _colorHandle;			/**< id of color attribute in vertex buffer*/
public:
	PolygonRenderer(std::vector<Vec2> polygon,
					const GLchar* vertexShaderSource, 
					const GLchar* fragmentShaderSource);
	virtual ~PolygonRenderer();

	virtual void onAdd();
	virtual void onRemove();
	virtual void onFrame();
};

#endif

