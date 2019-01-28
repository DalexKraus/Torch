#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
	_programId = glCreateProgram();

	//compilation stage
	unsigned int vertexShader = ShaderProgram::compileShader(GL_VERTEX_SHADER, vertexShaderCode);
	unsigned int fragmentShader = ShaderProgram::compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
	
	//attach shader programs
	glAttachShader(_programId, vertexShader);
	glAttachShader(_programId, fragmentShader);

	std::cout << "Called cosntructor" << std::endl;

	//Bind Shader attributes to VAO's VBO's
	bindAttributes();

	glBindAttribLocation(_programId, 0, "aPos");

	//linking stage
	glLinkProgram(_programId);

	//Check for any linking errors
	if (checkError(GL_LINK_STATUS, _programId))
	{
		std::cout << "[ERROR] Shader linking failed." << std::endl;
	}
	else std::cout << "[INFO] Shader compilation finished." << std::endl;
	
	//Delete shader sources, because we don't need them anymore,
	//as the program is already compiled and linked.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int ShaderProgram::compileShader(GLuint shaderType, const std::string& shaderSourceCode)
{
	unsigned int shaderId = glCreateShader(shaderType);
	const char* source = shaderSourceCode.c_str();
	
	//Atttach the shader source
	glShaderSource(shaderId, 1, &source, NULL);
	//Compile the shader
	glCompileShader(shaderId);
	
	//Check for any compilation errors
	if (checkError(GL_COMPILE_STATUS, shaderId))
	{
		glDeleteShader(shaderId);
		return 0;
	}

	//Return the id of the compiled shader
	return shaderId;
}

//Check if any errors occured during a specific stage of shader compilation
//
bool ShaderProgram::checkError(GLuint errorType, unsigned int program)
{
	int success;
	glGetShaderiv(program, errorType, &success);
	if (!success)
	{
		char errorLog[512];
		glGetShaderInfoLog(program, 512, NULL, errorLog);
		std::cout << "[ERROR] Shader compilation failed!\nErrorLog: " << errorLog << std::endl;
		glDeleteShader(program);
		return true;
	}
	return false;
}

//Returns a location of an uniform variable in the shader program
//
int ShaderProgram::getUniformLocation(std::string uniformName)
{
	const char* name = uniformName.c_str();
	return glGetUniformLocation(_programId, name);
}

//Bind a shader's attribute to a specific VBO
//
void ShaderProgram::bindAttribute(int attribute, std::string variableName)
{
	glBindAttribLocation(_programId, attribute, variableName.c_str());
}

int ShaderProgram::getProgramId()
{
	return _programId;
}

void ShaderProgram::start()
{
	glUseProgram(_programId);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}