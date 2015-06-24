#include <iostream>
#include <cmath>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Main.h>
#include <MasterEngine.h>

MasterEngine::MasterEngine(){
	win = CreateWindow(800, 600, "Hello World");
	SetEventCapture(win, EventKeyboard);
	SetKeyboardCallback(&MasterEngine::KeyboardEventHandler);
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

//SomeData
GLuint vao, vbo, ebo, vs, fs, fs1, sp, sp1;
float vertices[] = {
	//Pos 					//Color
     1.0f,  1.0f, 0.0f,		1.0, 0.0, 0.0,
    -1.0f,  1.0f, 0.0f,		0.0, 1.0, 0.0,
     0.0f,  0.0f, 0.0f,		0.0, 0.0, 1.0,
     1.0f, -1.0f, 0.0f,		1.0, 1.0, 0.0,
    -1.0f, -1.0f, 0.0f,		0.0, 1.0, 1.0
};
unsigned short indices[] = {0, 1, 2, 2, 3, 4};

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	vs = LoadShader("Shaders/Test.vs", GL_VERTEX_SHADER);
	fs = LoadShader("Shaders/Test.fs", GL_FRAGMENT_SHADER);
	//fs1 = LoadShader("Shaders/Test1.fs", GL_FRAGMENT_SHADER);
	sp = LinkShader(vs, fs);
	//sp1 = LinkShader(vs, fs1);
	glDeleteShader(vs);
	glDeleteShader(fs);
	//glDeleteShader(fs1);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
	
	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);		
		glEnableVertexAttribArray(1);		
	glBindVertexArray(0);

}
void MasterEngine::Render(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBindVertexArray(vao);
		glUseProgram(sp);
		//glUniform4f(glGetUniformLocation(sp, "MyColor"), 1.0f, (sin(glfwGetTime()/2) / 2) + 0.5, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned short), GL_UNSIGNED_SHORT, (void*)(0*sizeof(unsigned short)));
		//glUniform4f(glGetUniformLocation(sp, "MyColor"), 0.0f, 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned short), GL_UNSIGNED_SHORT, (void*)(3*sizeof(unsigned short)));
	glBindVertexArray(0);
	
}