#include"shader_h.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	//��ȡ�ļ��е���ɫ������
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//ȷ�����׳��쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//��ȡ������ɫ��
	try
	{
		//���ļ�
		vShaderFile.open(vertexPath);
		std::stringstream vShaderStream, fShaderStream;
		//����ɫ��������뵽��
		vShaderStream << vShaderFile.rdbuf();
		//�ر��ļ�
		vShaderFile.close();
		//�����д��봫��string
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		//�׳��쳣 : ������ɫ����ȡ����
		std::cout << "ERROR::SHADER::VERTEX_FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	//��ȡƬ����ɫ��
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
		//�׳��쳣 : Ƭ����ɫ����ȡ����
		std::cout << "ERROR::SHADER::FRAGMENT_FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	//��stringת��Ϊ��ɫ����ʶ���char����
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	//������ɫ��
	unsigned int vertex, fragment;
	//������ɫ������
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	//Ƭ����ɫ������
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	//��ɫ������
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	//ɾ��������ɫ����Ƭ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
};
Shader::~Shader()
{
	/*
	�ȴ��޸�
	*/
};
// ������ɫ��
// ------------------------------------------------------------------------
void Shader::use()
{
	glUseProgram(ID);
};
// ����uniform
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
//�жϴ���
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
