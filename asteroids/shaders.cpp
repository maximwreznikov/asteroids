#include "shaders.h"

//
const GLchar * glPositionColor_frag = 
"varying lowp vec4 theColor;						\n\
													\n\
void main()											\n\
{													\n\
	gl_FragColor = theColor;						\n\
}													\n\
";
const GLchar * glPositionColor_vert =
"attribute vec3 inPosition;								\n\
attribute vec3 inColor;									\n\
uniform mat4 MVP;										\n\
varying lowp vec4 theColor;								\n\
void main()												\n\
{														\n\
	vec4 v = vec4(inPosition, 1.0);						\n\
	gl_Position = MVP * v;								\n\
	theColor = vec4(inColor, 1.0);						\n\
}														\n\
";

const GLchar * glShellVertex =
"attribute vec3 inPosition;								\n\
uniform mat4 MVP;										\n\
void main()												\n\
{														\n\
	vec4 v = vec4(inPosition, 1.0);						\n\
	gl_Position = MVP * v;								\n\
}														\n\
";

const GLchar * glBlueFragment =
"													\n\
void main()											\n\
{													\n\
	gl_FragColor = vec4(0.0, 0.0, 0.8, 1.0);		\n\
}													\n\
";

const GLchar * glRedFragment =
"													\n\
void main()											\n\
{													\n\
	gl_FragColor = vec4(0.9, 0.0, 0.0, 1.0);		\n\
}													\n\
";

const GLchar * glBulletFragment =
"														\n\
varying lowp vec2 uv;									\n\
														\n\
precision lowp float;									\n\
void main()												\n\
{														\n\
	float border = 0.01;								\n\
	float radius = 0.5;									\n\
	vec4 color0 = vec4(0.0, 0.0, 0.0, 1.0);				\n\
	vec4 color1 = vec4(1.0, 0.0, 1.0, 1.0);				\n\
														\n\
	vec2 m = uv - vec2(0.5, 0.5);						\n\
	float dist = radius - sqrt(m.x * m.x + m.y * m.y);	\n\
														\n\
	float t = 0.0;										\n\
	if (dist > border)									\n\
		t = 1.0;										\n\
	else if (dist > 0.0)								\n\
		t = dist / border;								\n\
														\n\
	gl_FragColor = mix(color0, color1, t);				\n\
}"; 
const GLchar * glBulletVertex =
"attribute vec4 inPosition;							\n\
attribute vec2 textureUv;							\n\
uniform mat4 MVP;									\n\
varying lowp vec2 uv;								\n\
													\n\
void main()											\n\
{													\n\
	gl_Position = MVP * inPosition;					\n\
	gl_PointSize = 5.0;								\n\
	uv = textureUv;									\n\
}";

const GLchar * glPointFragment =
"													\n\
void main()											\n\
{													\n\
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);		\n\
}";
const GLchar * glPointVertex =
"attribute vec3 inPosition;							\n\
uniform mat4 MVP;									\n\
													\n\
void main()											\n\
{													\n\
	gl_Position = MVP * vec4(inPosition.xyz,1.);	\n\
	gl_PointSize = 2.0;								\n\
}";
