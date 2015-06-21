#include <iostream>
using namespace std;
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <Main.h>
#include <MasterEngine.h>

MasterEngine::MasterEngine(){
	win = CreateWindow(800, 600, "Hello World");
	SetEventCapture(win, EventKeyboard);
	SetKeyboardCallback(&MasterEngine::KeyboardEventHandler);
	Init();
}
void MasterEngine::Run(){
	Event e;	//Outside to save on Construction Destruction time.
	while(!glfwWindowShouldClose(win)){
		glfwPollEvents();
		//while(PullEvent(e)){
//			if(e.Type == EventWindowClose) cout << "Yaaaaay it is closing" << endl;
//		}
		Render();
		glfwSwapBuffers(win);
	}
}

//SomeData
int vbo, vs;
double vertices[] =
	{-0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f};

//Event Handlers
void MasterEngine::KeyboardEventHandler(GLFWwindow*, int key, int scancode, int action, int mod){
	switch(key){
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(win, true);
		break;
	}
}

//Core
void MasterEngine::Init(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glViewport(0, 0, 800, 600);

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//vs = glCreateShader(GL_VERTEX_SHADER);
}
void MasterEngine::Render(){
	glClear(GL_COLOR_BUFFER_BIT);
}