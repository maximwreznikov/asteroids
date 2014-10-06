#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <time.h>

#include "../asteroids/Logger.h"
#include "../asteroids/Engine.h"
#include "../asteroids/Entity.h"
#include "../asteroids/Game.h"

static Game _game;

bool gles_setupGraphics(int w, int h) 
{
	Engine::Instance()->SetupGraphics(w, h);

	_game.TestScene();	

    return true;
}

bool gles_renderFrame()
{
	static clock_t previousTime = clock();
	clock_t nowTime = clock();
	float dt = float(nowTime - previousTime) / CLOCKS_PER_SEC;

	bool playing = true;//_game.Update(dt);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);

	Engine::Instance()->OnFrame(dt);

	glDisable(GL_BLEND);

	previousTime = nowTime;
	return playing;
}

#ifndef WIN32
extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    gles_setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    gles_renderFrame();
}
#endif
