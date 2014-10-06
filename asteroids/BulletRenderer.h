#ifndef BulletRenderer_h
#define BulletRendererr_h

#include "RendererComponent.h"

class BulletRenderer :public RendererComponent
{
private:
	GLuint  _positionBuffer;
	//GLuint  _textureBuffer;
	//GLuint	_textureHandle;
public:
	BulletRenderer();
	~BulletRenderer();

	virtual void onAdd();
	virtual void onRemove();
	virtual void onFrame();
};

#endif

