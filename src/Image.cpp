#include <Image.h>

#include <cstdio>
#include <cstring>
#include <Misc.h>
#include <SOIL.h>

static unsigned char* ParsePNG(FILE*, unsigned int&, unsigned int&);

static const char* MagicNumber[] = {
	"",
	"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"			//PNG
};
static const unsigned int MagicWidth[] = {
	0,
	sizeof(MagicNumber[int(Image::Type::PNG)])
};
static unsigned char* (* const ParseType[])(FILE*, unsigned int&, unsigned int&) = {
	nullptr,
	ParsePNG
};

unsigned char* Image::Parse(const char* const fpath, unsigned int &Width, unsigned int &Height, const Type ft){
	if(ft >= Type::Count){
		DME::log("Bad File Type Enum");
		return nullptr;
	}

	//SOIL Support
	//SOIL will always execute unless specified the type.
	if(ft == Type::Null)
		return SOIL_load_image(fpath, (int*)&Width, (int*)&Height, 0, SOIL_LOAD_RGB);

	char temp[100];
	Width = Height = 0;

	FILE* file = fopen(fpath, "rb");
	if(file == nullptr){
		DME::log("Unable to open file: %s", fpath);
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
		if(MagicWidth[i] < MagicWidth[i-1]){
			DME::log("Fatal Error!!");
			fclose(file);
			return nullptr;
		}
		if(fread(temp, 1, MagicWidth[i] - MagicWidth[i-1], file) != MagicWidth[i] - MagicWidth[i-1]){
			DME::log("Unexpected error while reading file: %s", fpath);
			fclose(file);
			return nullptr;
		}
		if(memcmp(MagicNumber[i], temp, MagicWidth[i]) == 0)
			return ParseType[i](file, Width, Height);
	}
	
	DME::log("File %s has Unsupported Format!", fpath);
	fclose(file);
	return nullptr;
}

//Parsing
//Must close file before return.

//PNG
static unsigned char* ParsePNG(FILE* file, unsigned int &Width, unsigned int &Height){
	int  ChunkSize;
	char ChunkType[5] = {};

	//Reading First Chunk
	fread((char*)&ChunkSize, 1, 4, file); DME::ReverseByteOrder(ChunkSize);
	fread(ChunkType, 1, 4, file);
	if(memcmp(ChunkType, "IHDR", 4) && ChunkSize != 0x0D){
		DME::log("Corrupted PNG File! First invalid first chunk of type %s and size %d", ChunkType, ChunkSize);
		fclose(file);
		return nullptr;
	}
	
	
	
	fclose(file);
	return nullptr;
}