#include <GLES2/gl2.h>

#ifdef WIN32

#include <stdio.h>
#define  LOG_TAG    "gl2asteroids"
#define  LOGI(...)  printf(LOG_TAG); printf("\Info - "); printf(__VA_ARGS__); printf("\n")
#define  LOGE(...)  printf(LOG_TAG); printf("\tError - "); printf(__VA_ARGS__); printf("\n")

#else

#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "gl2asteroids"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif // WIN

void printGLString(const char *name, GLenum s);
void checkGlError(const char* op);