#include <Image.h>
#include <cstdio>
#include <cstring>

static const char* MagicNumber[] = {
	"",
	"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"};
static const unsigned int MagicWidth[] = {
	0,
	sizeof(MagicNumber[int(Image::Type::PNG)])
};
static char* ParsePNG(FILE*, unsigned int&, unsigned int&);
static char* (* const ParseType[])(FILE*, unsigned int&, unsigned int&) = {
	nullptr,
	ParsePNG
};

char* Image::Parse(const char* const fpath, unsigned int &Width, unsigned int &Height, const Type ft){
	char temp[100];
	
	FILE* file = fopen(fpath, "rb");
	if(file == nullptr){
		DME::log("Unable to open file: %s", fpath);
		Width = Height = 0;
		return nullptr;
	}

	if(ft != Type::Null){
		if(fread(temp, 1, MagicWidth[int(ft)], file) != MagicWidth[int(ft)]){
			DME::log("Unexpected error while reading file: %s", fpath);
			fclose(file);
			return nullptr;
		}
		if(memcmp(MagicNumber[int(ft)], temp, MagicWidth[int(ft)]) != 0){
			DME::log("File %s has Unsupported Format!", fpath);			//<<CANIMPROVE>>//	//Can be improved with 'goto exit'. It will decrease binary memory
			fclose(file);
			return nullptr;
		}
		return ParseType[int(ft)](file, Width, Height);
	}

	for(int i = 1; i < int(Type::Count); i++){
		if(fread(temp, 1, MagicWidth[i] - MagicWidth[i-1], file) != MagicWidth[i] - MagicWidth[i-1]){
			DME::log("Unexpected error while reading file: %s", fpath);
			fclose(file);
			return nullptr;
		}
		if(memcmp(MagicNumber[i], temp, MagicWidth[i]) != 0) continue;
		return ParseType[i](file, Width, Height);
	}
	
	DME::log("File %s has Unsupported Format!", fpath);
	fclose(file);
	return nullptr;
}

static char* ParsePNG(FILE* file, unsigned int &Width, unsigned int &Height){
	DME::log("I am PNG");
	fclose(file);
	return nullptr;
}