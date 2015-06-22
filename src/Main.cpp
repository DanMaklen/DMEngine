//#include <cstdio>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Main.h>
#include <MasterEngine.h>

static MasterEngine* __EnginePtr;

//Window
GLFWwindow* CreateWindow(int Width, int Height, const char* Title, int Properties){
	if(~Properties & WinPropResizable) glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* win = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
	glfwMakeContextCurrent(win);
	if(win == nullptr){DME::log("Error:: Unable to create window\n"); exit(-1);}
	return win;
}

//Callbacks Functions
static KeyboardCallbackFunc_t __KeyboardCallbackFunc = nullptr;
static CharStreamCallbackFunc_t __CharStreamCallbackFunc = nullptr;
static MousePosCallbackFunc_t __MousePosCallbackFunc = nullptr;
static MouseEnterCallbackFunc_t __MouseEnterCallbackFunc = nullptr;
static MouseKeyCallbackFunc_t __MouseKeyCallbackFunc = nullptr;
static MouseScrollCallbackFunc_t __MouseScrollCallbackFunc = nullptr;
static FileDropCallbackFunc_t __FileDropCallbackFunc = nullptr;
static WindowPosCallbackFunc_t __WindowPosCallbackFunc = nullptr;
static WindowResizeCallbackFunc_t __WindowResizeCallbackFunc = nullptr;
static WindowCloseCallbackFunc_t __WindowCloseCallbackFunc = nullptr;
static WindowRefreshCallbackFunc_t __WindowRefreshCallbackFunc = nullptr;
static WindowFocusCallbackFunc_t __WindowFocusCallbackFunc = nullptr;
static WindowIconifiedCallbackFunc_t __WindowIconifiedCallbackFunc = nullptr;
static FrameResizeCallbackFunc_t __FrameResizeCallbackFunc = nullptr;

//Polling Events
static queue<Event> __EventQ;

//Static callbacks
static void __KeyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mod){
	if(__KeyboardCallbackFunc != nullptr) (__EnginePtr->*__KeyboardCallbackFunc)(win, key, scancode, action, mod);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventKeyboard;
		ev.Keyboard.key = key;
		ev.Keyboard.scancode = scancode;
		ev.Keyboard.action = action;
		ev.Keyboard.mod = mod;
		__EventQ.push(ev);	
	}
}
static void __CharStreamCallback(GLFWwindow* win, unsigned int unicode){
	if(__CharStreamCallbackFunc != nullptr) (__EnginePtr->*__CharStreamCallbackFunc)(win, unicode);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventCharStream;
		ev.unicode = unicode;
		__EventQ.push(ev);
	}
}
static void __MousePosCallback(GLFWwindow* win, double xpos, double ypos){
	if(__MousePosCallbackFunc != nullptr) (__EnginePtr->*__MousePosCallbackFunc)(win, xpos, ypos);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventMousePos;
		ev.MousePos.xPos = xpos;
		ev.MousePos.yPos = ypos;
		__EventQ.push(ev);	
	}
}
static void __MouseEnterCallback(GLFWwindow* win, int Enter){
	if(__MouseEnterCallbackFunc != nullptr) (__EnginePtr->*__MouseEnterCallbackFunc)(win, bool(Enter));
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventMouseEnter;
		ev.Enter = bool(Enter);
		__EventQ.push(ev);
	}
}
static void __MouseKeyCallback(GLFWwindow* win, int key, int action, int mod){
	if(__MouseKeyCallbackFunc != nullptr) (__EnginePtr->*__MouseKeyCallbackFunc)(win, key, action, mod);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventMouseKey;
		ev.MouseKey.key = key;
		ev.MouseKey.action = action;
		ev.MouseKey.mod = mod;
		__EventQ.push(ev);
	}
}
static void __MouseScrollCallback(GLFWwindow* win, double xoff, double yoff){
	if(__MouseScrollCallbackFunc != nullptr) (__EnginePtr->*__MouseScrollCallbackFunc)(win, xoff, yoff);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventMouseScroll;
		ev.MouseScroll.xOff = xoff;
		ev.MouseScroll.yOff = yoff;
		__EventQ.push(ev);
	}
}
static void __FileDropCallback(GLFWwindow* win, int count, const char** fpath){
	if(__FileDropCallbackFunc != nullptr) (__EnginePtr->*__FileDropCallbackFunc)(win, count, fpath);
	else printf("Error:: FileDrop Event was enabled without setting a callback function\n");
}
static void __WindowPosCallback(GLFWwindow* win, int xPos, int yPos){
	if(__WindowPosCallbackFunc != nullptr) (__EnginePtr->*__WindowPosCallbackFunc)(win, xPos, yPos);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventWindowPos;
		ev.WindowPos.xPos = xPos;
		ev.WindowPos.yPos = yPos;
		__EventQ.push(ev);
	}
}
static void __WindowResizeCallback(GLFWwindow* win, int Width, int Height){
	if(__WindowResizeCallbackFunc != nullptr) (__EnginePtr->*__WindowResizeCallbackFunc)(win, Width, Height);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventWindowResize;
		ev.WindowSize.Width = Width;
		ev.WindowSize.Height = Height;
		__EventQ.push(ev);
	}
}
static void __WindowCloseCallback(GLFWwindow* win){
	if(__WindowCloseCallbackFunc != nullptr) (__EnginePtr->*__WindowCloseCallbackFunc)(win);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventWindowClose;
		__EventQ.push(ev);
	}
}
static void __WindowRefreshCallback(GLFWwindow* win){
	if(__WindowCloseCallbackFunc != nullptr) (__EnginePtr->*__WindowRefreshCallbackFunc)(win);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventWindowRefresh;
		__EventQ.push(ev);
	}
}
static void __WindowFocusCallback(GLFWwindow* win, int Focus){
	if(__WindowFocusCallbackFunc != nullptr) (__EnginePtr->*__WindowFocusCallbackFunc)(win, bool(Focus));
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventWindowFocus;
		ev.Focus = bool(Focus);
		__EventQ.push(ev);
	}
}
static void __WindowIconifiedCallback(GLFWwindow* win, int Iconified){
	if(__WindowIconifiedCallbackFunc != nullptr) (__EnginePtr->*__WindowFocusCallbackFunc)(win, bool(Iconified));
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventWindowIconified;
		ev.Iconified = bool(Iconified);
		__EventQ.push(ev);
	}
}
static void __FrameResizeCallback(GLFWwindow* win, int Width, int Height){
	if(__FrameResizeCallbackFunc != nullptr) (__EnginePtr->*__FrameResizeCallbackFunc)(win, Width, Height);
	else{
		Event ev;
		ev.win = win;
		ev.Type = EventFrameResize;
		ev.FrameSize.Width = Width;
		ev.FrameSize.Height = Height;
		__EventQ.push(ev);
	}
}

bool PullEvent(Event& e){
	if(__EventQ.size() == 0) return false;
	e = __EventQ.front(); __EventQ.pop();
	return true;
}
void SetEventCapture(GLFWwindow* win, int Events){
	if(Events & EventKeyboard) glfwSetKeyCallback(win, __KeyboardCallback);
	else glfwSetKeyCallback(win, nullptr);
	if(Events & EventCharStream) glfwSetCharCallback(win, __CharStreamCallback);
	else glfwSetCharCallback(win, nullptr);
	if(Events & EventMousePos) glfwSetCursorPosCallback(win, __MousePosCallback);
	else glfwSetCursorPosCallback(win, nullptr);
	if(Events & EventMouseEnter) glfwSetCursorEnterCallback(win, __MouseEnterCallback);
	else glfwSetCursorEnterCallback(win, nullptr);
	if(Events & EventMouseKey) glfwSetMouseButtonCallback(win, __MouseKeyCallback);
	else glfwSetMouseButtonCallback(win, nullptr);
	if(Events & EventMouseScroll) glfwSetScrollCallback(win, __MouseScrollCallback);
	else glfwSetScrollCallback(win ,nullptr);
	if(Events & EventFileDrop) glfwSetDropCallback(win, __FileDropCallback);
	else glfwSetDropCallback(win, nullptr);
	if(Events & EventWindowPos) glfwSetWindowPosCallback(win, __WindowPosCallback);
	else glfwSetWindowPosCallback(win, nullptr);
	if(Events & EventWindowResize) glfwSetWindowSizeCallback(win, __WindowResizeCallback);
	else glfwSetWindowSizeCallback(win, nullptr);
	if(Events & EventWindowClose) glfwSetWindowCloseCallback(win, __WindowCloseCallback);
	else glfwSetWindowCloseCallback(win, nullptr);
	if(Events & EventWindowRefresh) glfwSetWindowRefreshCallback(win, __WindowRefreshCallback);
	else glfwSetWindowRefreshCallback(win, nullptr);
	if(Events & EventWindowFocus) glfwSetWindowFocusCallback(win, __WindowFocusCallback);
	else glfwSetWindowFocusCallback(win, nullptr);
	if(Events & EventWindowIconified) glfwSetWindowIconifyCallback(win, __WindowIconifiedCallback);
	else glfwSetWindowIconifyCallback(win, nullptr);
	if(Events & EventFrameResize) glfwSetFramebufferSizeCallback(win, __FrameResizeCallback);
	else glfwSetFramebufferSizeCallback(win, nullptr);
}

void SetKeyboardCallback(KeyboardCallbackFunc_t func){__KeyboardCallbackFunc = func;}
void SetCharStreamCallback(CharStreamCallbackFunc_t func){__CharStreamCallbackFunc = func;}
void SetMousePosCallback(MousePosCallbackFunc_t func){__MousePosCallbackFunc = func;}
void SetMouseEnterCallback(MouseEnterCallbackFunc_t func){__MouseEnterCallbackFunc = func;}
void SetMouseKeyCallback(MouseKeyCallbackFunc_t func){__MouseKeyCallbackFunc = func;}
void SetMouseScrollCallback(MouseScrollCallbackFunc_t func){__MouseScrollCallbackFunc = func;}
void SetFileDropCallback(FileDropCallbackFunc_t func){__FileDropCallbackFunc = func;}
void SetWindowPosCallback(WindowPosCallbackFunc_t func){__WindowPosCallbackFunc = func;}
void SetWindowResizeCallback(WindowResizeCallbackFunc_t func){__WindowResizeCallbackFunc = func;}
void SetWindowCloseCallback(WindowCloseCallbackFunc_t func){__WindowCloseCallbackFunc = func;}
void SetWindowRefreshCallback(WindowRefreshCallbackFunc_t func){__WindowRefreshCallbackFunc = func;}
void SetWindowFocusCallback(WindowFocusCallbackFunc_t func){__WindowFocusCallbackFunc = func;}
void SetWindowIconifiedCallback(WindowIconifiedCallbackFunc_t func){__WindowIconifiedCallbackFunc = func;}
void SetFrameResizeCallback(FrameResizeCallbackFunc_t func){__FrameResizeCallbackFunc = func;}

//Main
int main(){
	if(glfwInit() != GL_TRUE){DME::log("Unable to initialize GLFW"); exit(-1);}
	GLFWwindow* tw = CreateWindow(100, 100, "");	//Temporary hack to initialize glew
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){DME::log("Unable to initialize GLEW"); exit(-1);}
	glfwDestroyWindow(tw);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	__EnginePtr = new MasterEngine;
	__EnginePtr->Run();
	delete __EnginePtr;

	glfwTerminate();
	return 0;
}

//Misc
unsigned int LoadShader(const char* fpath, GLenum ShaderType){
	int fsz;
	char* buf;
	int sid;

	FILE* file = fopen(fpath, "r");
	if(file == nullptr) {DME::log("Unable to load shaderfile: %s", fpath); return -1;}	//File Doesn't exit

	fseek(file, 0, SEEK_END);
  	fsz = ftell(file);
  	rewind(file);

  	buf = new char[fsz+1]; buf[fsz] = '\0';
  	if(buf == nullptr) return -1;	//out of memory;
  	if(fread(buf, 1, fsz, file) != fsz) return -1;	//Not all the file is read
	
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
  		delete[] error;
  		return -1;
  	}
  	return sid;
}

unsigned int LinkShader(unsigned int vsID, unsigned int fsID, bool del){
	int spID = glCreateProgram();
	glAttachShader(spID, vsID);
	glAttachShader(spID, fsID);
	glLinkProgram(spID);

	int success;
	glGetProgramiv(spID, GL_LINK_STATUS, &success);
	if(!success){
		DME::log("Shader Linking Faild: vsID(%u) fsID(%u)", vsID, fsID);
		char* error;
		int len;
		glGetProgramiv(spID, GL_INFO_LOG_LENGTH, &len);
		error = new char[len];
		cout << len << endl;
		glGetProgramInfoLog(spID, len, &len, error);
		DME::log("%s", error);

		glDeleteProgram(spID);
		delete[] error;
		return -1;
	}

	if(del){
		glDeleteShader(vsID);
		glDeleteShader(fsID);
	}
	return spID;
}