#include <Image.h>
#include <cstdio>
#include <cstring>

enum FileType{
	ftPNG									//PNG
};
static const char* MagicNumber[] = {
	"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"};
static const unsigned int MagicWidth[] = {
	sizeof(MagicNumber[ftPNG])
};
char* Image::Parse(const char* const fpath, unsigned int &Width, unsigned int &Height){
	char  temp[100];
	char* buff;

	FILE* file = fopen(fpath, "rb");
	if(file == nullptr){
		DME::log("Unable to load image: %s", fpath);
		Width = Height = 0;
		return nullptr;
	}

	if(fread(temp, 1, MagicWidth[ftPNG], file) != MagicWidth[ftPNG]){
		DME::log("Unexpected error while reading file: %s", fpath);
		return nullptr;
	}
	

}