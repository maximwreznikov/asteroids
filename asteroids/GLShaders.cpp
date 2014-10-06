#include "GLShaders.h"

#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Logger.h"

GLShader::GLShader()
{
	_loaded = false;
}

/**
@brief ������ ������ �� ������
@param sources ������ � ��������
@param type ��� �������
@return true, ���� ������ ������� �������������
*/
bool GLShader::loadShader(const GLchar * sources, int type)
{
	_shaderHandle = glCreateShader(type);

	glShaderSource(_shaderHandle, 1, &sources, nullptr);
	glCompileShader(_shaderHandle);
	//checkGlError("glCompileShader");

	int iCompilationStatus;
	glGetShaderiv(_shaderHandle, GL_COMPILE_STATUS, &iCompilationStatus);

	if (iCompilationStatus == GL_FALSE) return false;

	_type = type;
	_loaded = true;
	return true;
}

bool GLShader::isLoaded()
{
	return _loaded;
}


GLuint GLShader::getShaderID()
{
	return _shaderHandle;
}

/**
@brief ������� ������
*/
void GLShader::deleteShader()
{
	if(!isLoaded())return;
	_loaded = false;
	glDeleteShader(_shaderHandle);
}


GLShaderProgram::GLShaderProgram()
{
	_linked = false;
}

/**
@brief ������� ��������� ���������
*/
void GLShaderProgram::createProgram()
{
	_programHandle = glCreateProgram();
}

GLuint GLShaderProgram::getProgramID()
{
	return _programHandle;
}

/**
@brief �������� ������ � ��������� ���������
@param shader ������
@return true, ���� ������ ������� ��������
*/
bool GLShaderProgram::addShaderToProgram(GLShader* shader)
{
	if (!shader->isLoaded()) return false;

	glAttachShader(_programHandle, shader->getShaderID());

	return true;
}

/**
@brief ������������ ��������� ���������
*/
bool GLShaderProgram::linkProgram()
{
	glLinkProgram(_programHandle);
	int iLinkStatus;
	glGetProgramiv(_programHandle, GL_LINK_STATUS, &iLinkStatus);
	_linked = iLinkStatus == GL_TRUE;
	return _linked;
}

/**
@brief ������� ��������� ���������
*/
void GLShaderProgram::deleteProgram()
{
	if (!_linked) return;
	_linked = false;
	glDeleteProgram(_programHandle);
}

/**
@brief ������������ ��������� ���������
*/
void GLShaderProgram::useProgram()
{
	if (_linked) glUseProgram(_programHandle);
}