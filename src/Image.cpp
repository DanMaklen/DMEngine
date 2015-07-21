#include <Image.h>

#include <cstdio>
#include <cstring>
#include <Misc.h>
#include <SOIL.h>

//Maybe find a better way/organization for the Parse Function
#define __ParseFunction(__NAME) namespace __NAME{extern unsigned char* Parse(FILE*, unsigned int&, unsigned int&);}
//namespace{namespace PNG{extern unsigned char* Parse(FILE*, unsigned int&, unsigned int&);}}
namespace{
	namespace PNG{extern unsigned char* Parse(FILE*, unsigned int&, unsigned int&);}
}

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
	PNG::Parse
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
namespace{
///********************
///**********PNG
///********************
namespace PNG{
unsigned char* ReadChunk(FILE*);
unsigned char* Parse(FILE* file, unsigned int &Width, unsigned int &Height){
	unsigned int  ChunkSize, CRC;
	unsigned char BitDepth, ColorType, CompressionMethod, FilterMethod, InterlaceMethod;
	unsigned char ChunkType[5] = {};
	unsigned char buf[4 * 1024] = {};

	//Reading First Chunk
	//IHDR
	{
		fread((char*)&ChunkSize, 1, 4, file); DME::ReverseByteOrder(ChunkSize);
		fread(ChunkType, 1, 4, file);
		if(memcmp(ChunkType, "IHDR", 4) != 0 && ChunkSize != 13){
			DME::log("Corrupted PNG File! First invalid first chunk of type %s and size %d", ChunkType, ChunkSize);
			fclose(file);
			return nullptr;
		}
		fread((char*)&Width, 1, 4, file); DME::ReverseByteOrder(Width);
		fread((char*)&Height, 1, 4, file); DME::ReverseByteOrder(Height);
		fread((char*)&BitDepth, 1, 1, file);
		fread((char*)&ColorType, 1, 1, file);
		fread((char*)&CompressionMethod, 1, 1, file);
		fread((char*)&FilterMethod, 1, 1, file);
		fread((char*)&InterlaceMethod, 1, 1, file);
		fread((char*)&CRC, 1, 4, file); DME::(ReverseByteOrder(CRC));

		//CRC Chec
		//Currently not done

		//PNG Error Check
		if(BitDepth == 0 || (BitDepth - 1) & BitDepth || BitDepth > 16){
			DME::log("Corrupted PNG File! Invalid Bit Depth value of %hhu", BitDepth);
			fclose(file);
			return nullptr;
		}
		if(ColorType != 3 && ColorType & 1 || ColorType > 6){
			DME::log("Corrupted PNG File! Invalid Color Type value of %d", ColorType);
			fclose(file);
			return nullptr;
		}
		if(BitDepth == 16 && ColorType == 3 || BitDepth < 8 && ColorType != 0 && ColorType != 3){
			DME::log("Corrupted PNG File! Invalid combination of Bit Depth(%hhu) and Color Type(%hhu)", BitDepth, ColorType);
			fclose(file);
			return nullptr;
		}
		if(CompressionMethod != 0){
			DME::log("Corrupted PNG File! Invalid Compression Method value of %hhu.", CompressionMethod);
			fclose(file);
			return nullptr;
		}
		if(FilterMethod != 0){
			DME::log("Corrupted PNG File! Invalid Filter Method value of %hhu.", FilterMethod);
			fclose(file);
			return nullptr;	
		}
		if(InterlaceMethod != 0 && InterlaceMethod != 1){
			DME::log("Corrupted PNG File! Invalid Interlace Method value of %hhu.", InterlaceMethod);
			fclose(file);
			return nullptr;	
		}

		//DME Support Check
		if(BitDepth != 8 || ColorType != 2){
			DME::log("DMEngine PNG Parser currently support 8bit depth and Truecolor type. Please use the External(SOIL) parser for this file.");
			fclose(file);
			return nullptr;
		}
		if(InterlaceMethod != 0){
			DME::log("DMEngine PNG Parser currently does not support Interlacing. Please use the External(SOIL) parser for this file.")
			fclose(file);
			return nullptr;
		}
	}
	



	fclose(file);
	return nullptr;
}	
}

}