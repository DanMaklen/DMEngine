#ifndef __20150603_MASTERENGINE_H
#define __20150603_MASTERENGINE_H

typedef struct GLFWwindow GLFWwindow;

class MasterEngine{
	MasterEngine(const MasterEngine&) = delete;
	MasterEngine(MasterEngine&&) = delete;
private:
	GLFWwindow* win;

public:
	MasterEngine();
	void Run();

//Event Handlers
	void KeyboardEventHandler(GLFWwindow*, int, int, int, int);	

//Core
	void Init();
	void Render();
};

#endif