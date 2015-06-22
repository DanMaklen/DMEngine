#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Main.h>
#include <MasterEngine.h>

//SomeData
GLuint vao, vbo, vs, fs, sp;
float vertices[] =
	{-0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f};

MasterEngine::MasterEngine(){
	win = CreateWindow(800, 600, "Hello World");
	SetEventCapture(win, EventKeyboard);
	SetKeyboardCallback(&MasterEngine::KeyboardEventHandler);
	//if(glewInit() != GLEW_OK){DME::log("Unable to initialize GLEW"); exit(-1);}
	Init();
}
MasterEngine::~MasterEngine(){
	
}
void MasterEngine::Run(){
	Event e;
	while(!glfwWindowShouldClose(win)){
		glfwPollEvents();
		Render();
		glfwSwapBuffers(win);
	}
}

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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, 800, 600);

	vs = LoadShader("Shaders/Test.vs", GL_VERTEX_SHADER);
	fs = LoadShader("Shaders/Test.fs", GL_FRAGMENT_SHADER);
	sp = LinkShader(vs, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	
	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}
void MasterEngine::Render(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(sp);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	
}