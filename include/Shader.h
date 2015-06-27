#ifndef __20150627_Shader_H
#define __20150627_Shader_H

class Shader{
	Shader(const Shader&) = delete;		//No deep copy of shaders
public:
	unsigned int ID;
public:
	static unsigned int CompileShader(const char*, const unsigned int);
	static unsigned int LinkShader(const unsigned int, const unsigned int, const bool = false);
public:
	Shader(); //Empty Shader
	Shader(const unsigned int, const unsigned int);				//WARNING: This constructor doesn't clean up the shaders.
	Shader(const char*, const char*);
	Shader(Shader&&);
	~Shader();

	Shader& Set();	//Set Empty Shader
	Shader& Set(const unsigned int, const unsigned int); 		//WARNING: This function doesn't clean up the shaders.
	Shader& Set(const char*, const char*);

	bool isEmpty() const;

	void Attach() const;
	void Detach() const;
};

#endif