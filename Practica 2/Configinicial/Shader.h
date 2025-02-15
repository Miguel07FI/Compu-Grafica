
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
	GLuint Program;
	// Constructor generates the shader on the fly
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// Print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// Print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		// Print linking errors if any
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	// Uses the current shader
	void Use()
	{
		glUseProgram(this->Program);
	}
};

#endif




float vertices[] = {
	// Posición (x, y, z)    // Color (R, G, B)
	0.0f,  0.0f,  0.0f,    1.0f, 1.0f, 0.0f,  // A
	5.0f,  0.0f,  0.0f,    1.0f, 1.0f, 0.0f,  // B
	0.84f,  2.28f,  0.0f,  1.0f, 1.0f, 0.0f,  // C
	0.68f,  1.58f,  0.0f,  1.0f, 1.0f, 0.0f,  // D
	1.39f,  1.55f,  0.0f,  1.0f, 1.0f, 0.0f,  // E
	0.01f,  1.78f,  0.0f,  1.0f, 1.0f, 0.0f,  // F
	0.04f,  1.57f,  0.0f,  1.0f, 1.0f, 0.0f,  // G
	0.99f,  0.23f,  0.0f,  1.0f, 1.0f, 0.0f,  // H
	1.71f,  0.79f,  0.0f,  1.0f, 1.0f, 0.0f,  // I
	1.0f,  1.5f,  0.0f,   1.0f, 1.0f, 0.0f,  // J
	2.86f,  1.58f,  0.0f,  1.0f, 1.0f, 0.0f,  // K
	2.86f,  0.78f,  0.0f,  1.0f, 1.0f, 0.0f,  // L
	4.38f,  1.55f,  0.0f,  1.0f, 1.0f, 0.0f,  // M
	3.94f,  0.81f,  0.0f,  1.0f, 1.0f, 0.0f,  // N
	4.7f,  0.19f,  0.0f,  1.0f, 1.0f, 0.0f,  // O
	4.73f,  1.55f,  0.0f,  1.0f, 1.0f, 0.0f,  // P
	0.87f,  0.23f,  0.0f,  1.0f, 1.0f, 0.0f,  // Q
	0.98f,  1.38f,  0.0f,  1.0f, 1.0f, 0.0f,  // R
	4.84f,  0.23f,  0.0f,  1.0f, 1.0f, 0.0f   // S
};