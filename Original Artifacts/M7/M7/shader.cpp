#include "shader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>


Shader::Shader(std::string& vertexSource, std::string& fragmentSource)
{
	load(vertexSource, fragmentSource);
}

Shader::Shader(std::ifstream& source, std::ifstream& fsource) {

	std::stringstream vs;
	vs << source.rdbuf();
	source.close();

	std::stringstream fs;
	fs << fsource.rdbuf();
	fsource.close();

	std::string v = vs.str().c_str();
	std::string f = fs.str().c_str();

	load(v, f);
}

void Shader::Bind()
{
	//Use our triangle shader.
	glUseProgram(_shaderProgram);
}

void Shader::setMat4(const std::string& uniformName, glm::mat4& mat4)
{
	auto uniformLoc = getUniformLocation(uniformName);
	if (uniformLoc != -1) {
		Bind();
		glUniformMatrix4fv( uniformLoc, 1, GL_FALSE, glm::value_ptr(mat4));
	}
}


void Shader::setVec3(const std::string& uniformName, glm::vec3& vec3)
{
	auto uniformLoc = getUniformLocation(uniformName);
	if (uniformLoc != -1) {
		Bind();
		glUniform3fv(uniformLoc, 1, &vec3[0]);
		//glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(vec3));
	}
	else {
		std::cout << uniformName<<" location not found" <<std::endl;
	}
}

void Shader::load(std::string& vertexSource, std::string& fragmentSource)
{
	const GLchar* vShaderCode = vertexSource.c_str();
	const GLchar* fShaderCode = fragmentSource.c_str();

	//compiling vertex shader
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infolog);
		std::cerr << "Error vertex shader compilation fail" << infolog << std::endl;
	}

	//compiling color shader
	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infolog);
		std::cerr << "ERROR: fragment shader compilation fail" << infolog << std::endl;
	}

	//creating shader program
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(_shaderProgram, 512, nullptr, infolog);
		std::cerr << "ERROR!!: 	shader program link fail" << infolog << std::endl;
	}

	//cleaning up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
	return glGetUniformLocation(_shaderProgram, uniformName.c_str());
}
