#ifndef __20150603_MASTERENGINE_H
#define __20150603_MASTERENGINE_H

#include <Shader.h>

typedef struct GLFWwindow GLFWwindow;

class MasterEngine{
	MasterEngine() = delete;
	MasterEngine(const MasterEngine&) = delete;
	MasterEngine(MasterEngine&&) = delete;
private:
	GLFWwindow* win;
	Shader sp;

public:
	MasterEngine(GLFWwindow*);
	~MasterEngine();
	void Run();

//Event Handlers
	void KeyboardEventHandler(GLFWwindow*, int, int, int, int);	

//Core
	void Init();
	void Render();
};

#endif