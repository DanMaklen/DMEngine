Current Features:
	-Creating Window
	-File Logging System
	-Shader Class
	-Shader File Compiling
	-Shader Program Lingking
	-Reverse Byte Order for Little-Endian / Big-Endian conversion.
	-Temporary Support for several image types using SOIL until image parsers are complete.

Working On:
	-Image/Texture Parsing (PNG Parsing)

Future Ideas:
	-ini File for settings like log folder location.
	-Function to read a file and put it in a char*? Is it needed (Needed 1 time(s) in Shader class). (Or maybe a class that handels error reporting in the log).

Improvments:
	-Logs divided into files (by date or maybe by session).
	-Logs preceded with basic information like time? Kind of message like Error or Warning or maybe information?
	-Better error handeling or termination (better than "exit");
	-Tri-like structure for faster Magic Number comparison in Image::Parse (Possibly not needed and its overhead will not be worth it or maybe even cause performance drop, need testing\calculating)
	-'ReverseByteOrder' have a good chance to be platform dependent, so look for a cross-platform solution or confirm platform independability.
	-Better organization for 'Parse' functions in 'Image.cpp'
	-Missing CRC checking and some features in PNG parser.

Known Bugs:

Dependencies:
	-GLFW v3.1.1
	-GLEW v1.12.0
	-OpenGL 4.4
	-SOIL (In linux, need to add it in NMakefile for windows)

Collaboration Guide:
	-Add the tag "//<<IMPROVE>>//" If there is a possible performance improvment that you are just lazy to do right now :D Please hit to the kind of improvment next to it.
	-Add the tag "//<<CANIMPROVE>>//" If there is a possible performance improvment but might make the code less readable or maintainable. Please hit to the kind of improvment next to it.
	