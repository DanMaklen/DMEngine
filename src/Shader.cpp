#include <cstdio>
#include <GL/glew.h>
#include <Shader.h>

unsigned int Shader::CompileShader(const char* fpath, unsigned int ShaderType){
	unsigned long long fsz;
	char* buf;
	unsigned int sid;

	FILE* file = fopen(fpath, "rb");
	if(file == nullptr){					//File Doesn't exit
		DME::log("Unable to load shaderfile: %s", fpath);
		return -1;
	}

	fseek(file, 0, SEEK_END);
  	fsz = ftell(file);
  	rewind(file);

  	buf = new char[fsz+1]();
  	if(fread(buf, 1, fsz, file) != fsz){	//Not all the file is read
  		DME::log("Unexpected error while reading file: %s", fpath);
  		delete[] buf;
  		return -1;
  	}
	
	fclose(file);

  	sid = glCreateShader(ShaderType);
  	glShaderSource(sid, 1, &buf, nullptr);
  	glCompileShader(sid);

  	//Compilation Error handeling
  	int Success;
  	glGetShaderiv(sid, GL_COMPILE_STATUS, &Success);
  	if(!Success){
  		DME::log("Shader Compilation Failed: %s.", fpath);
  		char* error;
  		int len;
  		glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &len);
  		error = new char[len];
  		glGetShaderInfoLog(sid, len, &len, error);
  		DME::log("%s", error);

  		glDeleteShader(sid);
  		delete[] error, buf;
  		return -1;
  	}
  	delete[] buf;
  	return sid;
}
unsigned int Shader::LinkShader(const unsigned int vsID, const unsigned int fsID, const bool CleanUp){
	int spID = glCreateProgram();
	glAttachShader(spID, vsID);
	glAttachShader(spID, fsID);
	glLinkProgram(spID);

	int Success;
	glGetProgramiv(spID, GL_LINK_STATUS, &Success);
	if(!Success){
		DME::log("Shader Linking Faild: vsID(%u) fsID(%u)", vsID, fsID);
		char* error;
		int len;
		glGetProgramiv(spID, GL_INFO_LOG_LENGTH, &len);
		error = new char[len];
		glGetProgramInfoLog(spID, len, &len, error);
		DME::log("%s", error);

		glDeleteProgram(spID);
		delete[] error;
		return -1;
	}
	if(CleanUp){
		glDeleteShader(vsID);
		glDeleteShader(fsID);
	}
	return spID;
}

Shader::Shader() : ID(0){}
Shader::Shader(const unsigned int vsID, const unsigned int fsID) : ID(LinkShader(vsID, fsID, false)){}
Shader::Shader(const char* vsfpath, const char* fsfpath) : ID(LinkShader(CompileShader(vsfpath, GL_VERTEX_SHADER), CompileShader(fsfpath, GL_FRAGMENT_SHADER), true)){}
Shader::Shader(Shader&& cpy) : ID(cpy.ID){cpy.ID = 0;}
Shader::~Shader(){if(ID != 0) glDeleteProgram(ID);}

Shader& Shader::Set(){
	if(ID != 0) glDeleteProgram(ID);
	ID = 0;
}
Shader& Shader::Set(const unsigned int vsID, const unsigned int fsID){
	if(ID != 0) glDeleteProgram(ID);
	ID = LinkShader(vsID, fsID, false);
}
Shader& Shader::Set(const char* vsfpath, const char* fsfpath){
	if(ID != 0) glDeleteProgram(ID);
	ID = LinkShader(CompileShader(vsfpath, GL_VERTEX_SHADER), CompileShader(fsfpath, GL_FRAGMENT_SHADER), true);
}

bool Shader::isEmpty() const{return ID == 0;}

void Shader::Attach() const{glUseProgram(ID);}
void Shader::Detach() const{glUseProgram(0);}