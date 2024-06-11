#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <filesystem>


class Shader
{
public:
	Shader() = default;
	Shader(std::string& vertexSource, std::string& fragmentSource);
	Shader(std::ifstream& source, std::ifstream& fsource);
	void Bind();
	void setMat4(const std::string& uniformName, glm::mat4& mat4);
	void setVec3(const std::string& uniformName, glm::vec3& vec3);
private:
	void load(std::string& vertexSource, std::string& fragmentSource);
	GLint getUniformLocation(const std::string& uniformName);
	GLuint _shaderModule{};
	GLuint _shaderProgram{};
};

