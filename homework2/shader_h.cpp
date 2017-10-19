#include"shader_h.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	//读取文件中的着色器代码
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//确保能抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//读取顶点着色器
	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		std::stringstream vShaderStream, fShaderStream;
		//将着色器代码读入到流
		vShaderStream << vShaderFile.rdbuf();
		//关闭文件
		vShaderFile.close();
		//将流中代码传入string
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		//抛出异常 : 顶点着色器读取错误
		std::cout << "ERROR::SHADER::VERTEX_FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	//读取片段着色器
	try
	{
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		fShaderStream << fShaderFile.rdbuf();
		fShaderFile.close();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		//抛出异常 : 片段着色器读取错误
		std::cout << "ERROR::SHADER::FRAGMENT_FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	//将string转换为着色器可识别的char对象
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	//编译着色器
	unsigned int vertex, fragment;
	//顶点着色器部分
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	//片段着色器部分
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	//着色器程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	//删除顶点着色器和片段着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
};
Shader::~Shader()
{
	/*
	等待修改
	*/
};
// 启用着色器
// ------------------------------------------------------------------------
void Shader::use()
{
	glUseProgram(ID);
};
// 传送uniform
// ------------------------------------------------------------------------
void Shader::set_bool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
};
// ------------------------------------------------------------------------
void Shader::set_int(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
};
// ------------------------------------------------------------------------
void Shader::set_float(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
};
//判断错误
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
};
