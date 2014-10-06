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
@brief Грузит шейдер из строки
@param sources строка с шейдером
@param type тип шейдера
@return true, если шейдер успешно скомпилирован
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
@brief Удаляет шейдер
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
@brief Создать шейдерную программу
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
@brief Добавить шейдер к шейдерной программе
@param shader шейдер
@return true, если шейдер успешно добавлен
*/
bool GLShaderProgram::addShaderToProgram(GLShader* shader)
{
	if (!shader->isLoaded()) return false;

	glAttachShader(_programHandle, shader->getShaderID());

	return true;
}

/**
@brief Скомпоновать шейдерную программу
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
@brief Удалить шейдерную программу
*/
void GLShaderProgram::deleteProgram()
{
	if (!_linked) return;
	_linked = false;
	glDeleteProgram(_programHandle);
}

/**
@brief Использовать шейдерную программу
*/
void GLShaderProgram::useProgram()
{
	if (_linked) glUseProgram(_programHandle);
}