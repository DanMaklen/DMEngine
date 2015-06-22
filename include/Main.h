//This file is to help encapsulating GLFW into c++ opbject oriented fation, it is not neccessery if GLFW in C-like.
//This event system will override the callback fuctionalities for set events only. So it is possible to use polling for some events
//	and callbacks for other events.

#ifndef __20150604_MAIN_H
#define __20150604_MAIN_H

class MasterEngine;

//Windows
typedef struct GLFWwindow GLFWwindow;
enum WindowProperty{WinPropResizable=1};
extern GLFWwindow* CreateWindow(int, int, const char*, int = WinPropResizable);

//Events
enum EventType{	EventKeyboard=0x0001, EventCharStream=0x0002, EventMousePos=0x0004, EventMouseEnter=0x0008,
				EventMouseKey=0x0010, EventMouseScroll=0x0020, EventFileDrop=0x0040, EventWindowPos=0x0080,
				EventWindowResize=0x0100, EventWindowClose=0x0200, EventWindowRefresh=0x0400, EventWindowFocus=0x0800,
				EventWindowIconified=0x1000, EventFrameResize=0x2000
			};
class Event{
private:
	struct KeyboardEvent_t{int key, scancode, action, mod;};
	struct MousePosEvent_t{double xPos, yPos;};
	struct MouseKeyEvent_t{int key, action, mod;};
	struct MouseScrollEvent_t{double xOff, yOff;};
	struct WindowPosEvent_t{int xPos, yPos;};
	struct WindowResizeEvent_t{int Width, Height;};
	struct FrameResizeEvent_t{int Width, Height;};
public:
	GLFWwindow* win;
	EventType Type;

	union{
		KeyboardEvent_t Keyboard;
		unsigned int unicode;
		MousePosEvent_t MousePos;
		bool Enter;
		MouseKeyEvent_t MouseKey;
		MouseScrollEvent_t MouseScroll;
		WindowPosEvent_t WindowPos;
		WindowResizeEvent_t WindowSize;
		bool Focus;
		bool Iconified;
		FrameResizeEvent_t FrameSize;
	};
};

extern bool PullEvent(Event&);
extern void SetEventCapture(GLFWwindow*, int);

typedef void (MasterEngine::*KeyboardCallbackFunc_t)(GLFWwindow*, int, int, int, int);
typedef void (MasterEngine::*CharStreamCallbackFunc_t)(GLFWwindow*, unsigned int);
typedef void (MasterEngine::*MousePosCallbackFunc_t)(GLFWwindow*, double, double);
typedef void (MasterEngine::*MouseEnterCallbackFunc_t)(GLFWwindow*, bool);
typedef void (MasterEngine::*MouseKeyCallbackFunc_t)(GLFWwindow*, int, int, int);
typedef void (MasterEngine::*MouseScrollCallbackFunc_t)(GLFWwindow*, double, double);
typedef void (MasterEngine::*FileDropCallbackFunc_t)(GLFWwindow*, int, const char**);
typedef void (MasterEngine::*WindowPosCallbackFunc_t)(GLFWwindow*, int, int);
typedef void (MasterEngine::*WindowResizeCallbackFunc_t)(GLFWwindow*, int, int);
typedef void (MasterEngine::*WindowCloseCallbackFunc_t)(GLFWwindow*);
typedef void (MasterEngine::*WindowRefreshCallbackFunc_t)(GLFWwindow*);
typedef void (MasterEngine::*WindowFocusCallbackFunc_t)(GLFWwindow*, bool);
typedef void (MasterEngine::*WindowIconifiedCallbackFunc_t)(GLFWwindow*, bool);
typedef void (MasterEngine::*FrameResizeCallbackFunc_t)(GLFWwindow*, int, int);

extern void SetKeyboardCallback(KeyboardCallbackFunc_t);
extern void SetCharStreamCallback(CharStreamCallbackFunc_t);
extern void SetMousePosCallback(MousePosCallbackFunc_t);
extern void SetMouseEnterCallback(MousePosCallbackFunc_t);
extern void SetMouseKeyCallback(MouseKeyCallbackFunc_t);
extern void SetMouseScrollCallback(MouseScrollCallbackFunc_t);
extern void SetFileDropCallback(FileDropCallbackFunc_t);
extern void SetWindowPosCallback(WindowPosCallbackFunc_t);
extern void SetWindowResizeCallback(WindowResizeCallbackFunc_t);
extern void SetWindowCloseCallback(WindowCloseCallbackFunc_t);
extern void SetWindowRefreshCallback(WindowRefreshCallbackFunc_t);
extern void SetWindowFocusCallback(WindowFocusCallbackFunc_t);
extern void SetWindowIconifiedCallback(WindowIconifiedCallbackFunc_t);
extern void SetFrameResizeCallback(FrameResizeCallbackFunc_t);

//Misc
extern unsigned int LoadShader(const char*, GLenum);
extern unsigned int LinkShader(unsigned int, unsigned int, bool = false);
#endif
