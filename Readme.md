Current Features:
	-Creating Window
	-File Logging System
	-Shader Class
	-Shader File Compiling
	-Shader Program Lingking
	
Working On:
	-Image/Texture Parsing

Future Ideas:
	-ini File for settings like log folder location.
	-Function to read a file and put it in a char*? Is it needed (Needed 1 time(s) in Shader class).

Improvments:
	-Logs divided into files (by date or maybe by session).
	-Logs preceded with basic information like time? Kind of message like Error or Warning or maybe information?
	-Better error handeling or termination (better than "exit");
	-Tri-like structure for faster Magic Number comparison in Image::Parse (Possibly not needed and its overhead will not be worth it or maybe even cause performance drop, need testing\calculating)
Known Bugs:

Dependencies:
	-GLFW v3.1.1
	-GLEW v1.12.0
	-OpenGL 4.4

Collaboration Guide:
	-Add the tag "//<<IMPROVE>>//" If there is a possible performance improvment that you are just lazy to do right now :D Please hit to the kind of improvment next to it.
	-Add the tag "//<<CANIMPROVE>>//" If there is a possible performance improvment but might make the code less readable or maintainable. Please hit to the kind of improvment next to it.
	