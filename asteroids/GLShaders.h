#ifndef CShader_h
#define CShader_h

#include <GLES2/gl2.h>

/**
@brief ������ 
@detailed ������� ��� �������, ����� ��� �������� � ���������� �������
*/
class GLShader
{
private:
	GLuint	_shaderHandle;			/**< ID of shader */
	int		_type;					/**< GL_VERTEX_SHADER, GL_FRAGMENT_SHADER... */
	bool	_loaded;				/**< Whether shader was loaded and compiled */

public:
	GLShader();

	bool loadShader(const GLchar * sources, int type);
	void deleteShader();

	bool isLoaded();
	GLuint getShaderID();
};

/**
@brief ��������� ���������
@detailed ������� ��� ��������� ��������� OpenGL, ����� ��� �������� ������������� ��������
*/
class GLShaderProgram
{
private:
	GLuint	_programHandle;		/**< ID of program */
	bool	_linked;			/**< Whether program was linked and is ready to use */

public:
	GLShaderProgram();

	void createProgram();
	void deleteProgram();

	bool addShaderToProgram(GLShader* shShader);
	bool linkProgram();

	void useProgram();

	GLuint getProgramID();
};

#endif