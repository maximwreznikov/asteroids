#include "RenderManager.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Logger.h"
#include "Transformation.h"

RenderManager::RenderManager()
{
	// Позиция в  (0,0,5)мировых координат
	// И смотрит в центр экрана
	// Верх камеры смотрит вверх
	CameraView = Mat4(1.0f, 0.0f, 0.0f, 0.0f,
					  0.0f, 1.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 1.0f, -5.0f,
					  0.0f, 0.0f, 0.0f, 1.0f);
}

RenderManager::~RenderManager()
{
}

void RenderManager::InitView(int width, int height)
{
	_widthScreen = width;
	_heightScreen = height;

	_widthView = float(width / ScaleX) / 2.0f;
	_heightView = float(height / ScaleY) / 2.0f;

	_projection = Ortho(-_widthView, _widthView, -_heightView, _heightView, -5.0f, 5.0f);

	Transformation::GWorldMatrix = _projection * CameraView;

	glViewport(0, 0, _widthScreen, _heightScreen);
	//checkGlError("glViewport");

	// clear screen with color
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}

void RenderManager::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	for (HandleRenderer obj : _components)
	{
		obj->onFrame();
	}	
}

float RenderManager::GetViewWidth()
{ 
	return _widthView; 
}
float RenderManager::GetViewHeight()
{ 
	return _heightView; 
}
