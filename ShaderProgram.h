#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <string>

class ShaderProgram
{
	private:
		unsigned int _programId;
		unsigned int compileShader(GLuint shaderType, const std::string& shaderSourceCode);
		bool checkError(GLuint errorType, unsigned int program);

	public:
		ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
		void bindAttribute(int attribute, std::string variableName);
		int getUniformLocation(std::string uniformName);
		int getProgramId();
		void start();
		void stop();

	protected:
		virtual void bindAttributes() {};
};

#endif