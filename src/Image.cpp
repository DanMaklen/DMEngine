#include <Image.h>

#include <cstdio>
#include <cstring>
#include <Misc.h>
#include <SOIL.h>
#include <cstdlib>

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
int zlibParse(unsigned char* Result, const unsigned int sz, const unsigned char* buf, const unsigned int bufSize){
	unsigned short LEN;

	if(*buf & 0x0F == 8 || *buf & 0xF0 > 7){
		DME::log("Corrupted zlib format. First byte have invalid combination of CM and CINFO flags.");
		return -1;
	}
	if(DME::ReverseByteOrder(*(unsigned short*)buf) % 31 != 0){
		DME::log("Corrupted zlib format. First 2 bytes is not divisible by 31.");
		return -1;
	}
	if(*buf++ != 0x78){
		DME::log("DMEngine zlibParse currently support only zlib compression method of value \'0x78\'.");
		return -2;
	}

	if(*buf++ & 0x20) buf+= 4;	//Skipping DICTID
	//DEFLATE\INFLATE
	while(DME::log("%x", *buf), ~*buf & 0x01){	//Block
		
		switch(*buf & 0x06){
		case 0x00:	//Uncompressed.
			DME::log() << "Uncompressed";
			buf++;
			LEN = DME::ReverseByteOrder(*(unsigned short*)buf);
			buf += 4;
			memcpy(Result, buf, LEN);
			Result += LEN;
			buf += LEN;
			return;
		case 0x02:	//Compressed with fixed Huffman codes.
			DME::log() << "Compressed with fixed Huffman codes";
			return 0;
		case 0x04:	//Compressed with dynamic Huffman codes.
			DME::log() << "Compressed with dynamic Huffman codes";
			return 0;
		case 0x06:	//Reserved (error!)
			DME::log("Corrupted DEFLATE\\INFLATE format. In a block BTYPE is set to (11).");
			return -1;
		default:	//WTF?
			DME::log("Unexpected error while reading DEFLATE\\INFLATE block with first byte %x", *buf);
			return -3;
		}

		//break;
	}

	return 0;
}
unsigned char* Parse(FILE* file, unsigned int &Width, unsigned int &Height){
	//<<IMPROVE>>//Read the chunk gradually instead of reading the whole chunk at once.
	unsigned int  ChunkSize, CRC, bufSize = 0;
	unsigned char BitDepth, ColorType, CompressionMethod, FilterMethod, InterlaceMethod;
	unsigned char ChunkType[5] = {};
	unsigned char *Result = nullptr, *tbuf = nullptr, *buf = new unsigned char[bufSize];
	//Reading First Chunk
	//IHDR Chunk
	{
		fread((char*)&ChunkSize, 1, 4, file); ChunkSize = DME::ReverseByteOrder(ChunkSize);
		fread(ChunkType, 1, 4, file);
		if(memcmp(ChunkType, "IHDR", 4) != 0 && ChunkSize != 13){
			DME::log("Corrupted PNG File! First invalid first chunk of type %s and size %d", ChunkType, ChunkSize);
			fclose(file);
			return nullptr;
		}
		fread((char*)&Width, 1, 4, file); Width = DME::ReverseByteOrder(Width);
		fread((char*)&Height, 1, 4, file); Height = DME::ReverseByteOrder(Height);
		fread((char*)&BitDepth, 1, 1, file);
		fread((char*)&ColorType, 1, 1, file);
		fread((char*)&CompressionMethod, 1, 1, file);
		fread((char*)&FilterMethod, 1, 1, file);
		fread((char*)&InterlaceMethod, 1, 1, file);
		fread((char*)&CRC, 1, 4, file); CRC = DME::ReverseByteOrder(CRC);

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
			DME::log("DMEngine PNG Parser currently does not support Interlacing. Please use the External(SOIL) parser for this file.");
			fclose(file);
			return nullptr;
		}
	}
	
	//Other Chunks
	{
		fread((char*)&ChunkSize, 1, 4, file); ChunkSize = DME::ReverseByteOrder(ChunkSize);
		fread(ChunkType, 1, 4, file);

		while(memcmp(ChunkType, "IEND", 4) != 0){
			if(ChunkType[0] >= 'a' && ChunkType[0] <= 'z'){	//Not Critical
				//Skipping for now
				unsigned char dump[ChunkSize];
				fread(dump, 1, ChunkSize, file);
			}
			else if(memcmp(ChunkType, "IDAT", 4) == 0){	//There is an unknown bug here
				tbuf = buf;
				buf = new unsigned char[bufSize + ChunkSize];
				memcpy(buf, tbuf, bufSize);
				delete[] tbuf;
				fread(buf + bufSize, 1, ChunkSize, file);
				bufSize += ChunkSize;
			}
			else{	//Other Critical Chunks
				DME::log("DMEngine PNG Parser currently does not support critical chunks other than \'IDAT\'. Please use the External(SOIL) parser for this file.");
				fclose(file);
				return nullptr;
			}
			fread((char*)&CRC, 1, 4, file); CRC = DME::ReverseByteOrder(CRC);
			fread((char*)&ChunkSize, 1, 4, file); ChunkSize = DME::ReverseByteOrder(ChunkSize);
			fread(ChunkType, 1, 4, file);
		}
		//Reading IEND CRC
		fread((char*)&CRC, 1, 4, file); CRC = DME::ReverseByteOrder(CRC);
		
		if(ChunkSize != 0){
			DME::log("Corrupted PNG File! Last chunk has size of %u.", ChunkSize);
			fclose(file);
			delete [] Result;
			return nullptr;
		}
	}

	//Decompression
	if(ColorType == 2) Result = new unsigned char[3 * Width * Height]();
	//else if(ColorType == 6) Result = new unsigned char[4 * Width * Height]();
	zlibParse(Result, Width * Height, buf, bufSize);
	
	delete[] buf;
	fclose(file);
	return Result;
}	
}

}