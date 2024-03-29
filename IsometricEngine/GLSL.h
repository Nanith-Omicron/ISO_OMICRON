#pragma once
#pragma once

#include <string>
#include "ressourceManager.hpp"
 


 
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void addAttribute(const std::string& attributeName);

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

		void linkShaders();

		GLuint getUniformLocation(const std::string& uniformName);

		void use();

		void unuse();

		void dispose();


	private:
		void compileShader(const char* source, const std::string& m_entityName, GLint shaderID);


		GLuint m_programID;
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
		int m_numAttrib;

	};

 