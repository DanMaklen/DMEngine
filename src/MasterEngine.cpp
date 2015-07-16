#include <iostream>
#include <cmath>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Main.h>
#include <MasterEngine.h>
#include <Shader.h>
#include <Image.h>

MasterEngine::MasterEngine(GLFWwindow* ParentWindow) : win(ParentWindow){
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
GLuint vao, vbo, ebo, tid;
float vertices[] = {
	// Positions          // Colors           // Texture Coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
};
GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

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
	
	sp.Set("shaders/Test.vs", "shaders/Test.fs");
	//buf = Image::Parse("textures/Test.png", W, H);

	unsigned int width, height;
	unsigned char* image = Image::Parse("textures/Test3.png", width, height, Image::Type::PNG);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenTextures(1, &tid);

	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(0);		
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	
	glBindTexture(GL_TEXTURE_2D, tid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void MasterEngine::Render(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	sp.Attach();
	glBindTexture(GL_TEXTURE_2D, tid);
	
	glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}