#pragma comment (lib,"opengl32.lib")
#include <windows.h> 
#include <memory>
#include <stdlib.h>
#include "gl_code.h"
#include "../asteroids/Logger.h"

///
// Initialize the shader and program object
//
int Init(ESContext *esContext)
{
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

	glSetupGraphics(esContext->width, esContext->height);
	return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext)
{
	glRenderFrame();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

int main(int argc, char *argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, TEXT("Asteroid"), 320, 480, ES_WINDOW_RGB);

	if (!Init(&esContext))
		return -1;

	esRegisterDrawFunc(&esContext, Draw);

	esMainLoop(&esContext);
}