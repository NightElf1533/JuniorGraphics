#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
	public:
		unsigned int ID;
		Shader(std::string vertex_shader_file, std::string framgment_shader_file);
		~Shader();
		void use();//using this Shader
		void set_bool(const std::string & name, bool value) const;
		void set_int(const std::string & name, int value) const;
		void set_float(const std::string & name, float value)const;
	private:
		void checkCompileErrors(unsigned int shader, std::string type);
};


#endif
