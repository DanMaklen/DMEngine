#include <Misc.h>

namespace DMEngine{
void ReverseByteOrder(short& val){
	val =	(val & 0x00FFu) << 010 |
			(val & 0xFF00u) >> 010 ;
}
void ReverseByteOrder(int& val){
	val =	(val & 0x000000FFu) << 030 |
			(val & 0x0000FF00u) << 010 |
			(val & 0x00FF0000u) >> 010 |
			(val & 0xFF000000u) >> 030 ;
}
void ReverseByteOrder(long& val){
	val = 	(val & 0x000000FFul) << 030 |
			(val & 0x0000FF00ul) << 010 |
			(val & 0x00FF0000ul) >> 010 |
			(val & 0xFF000000ul) >> 030 ;
}
void ReverseByteOrder(long long& val){
	val =	(val & 0x00000000000000FFull) << 070 |
			(val & 0x000000000000FF00ull) << 050 |
			(val & 0x0000000000FF0000ull) << 030 |
			(val & 0x00000000FF000000ull) << 010 |
			(val & 0x000000FF00000000ull) >> 010 |
			(val & 0x0000FF0000000000ull) >> 030 |
			(val & 0x00FF000000000000ull) >> 050 |
			(val & 0xFF00000000000000ull) >> 070 ;
}
void ReverseByteOrder(unsigned short& val){
	val =	(val & 0x00FFu) << 010 |
			(val & 0xFF00u) >> 010 ;
}
void ReverseByteOrder(unsigned int& val){
	val =	(val & 0x000000FFu) << 030 |
			(val & 0x0000FF00u) << 010 |
			(val & 0x00FF0000u) >> 010 |
			(val & 0xFF000000u) >> 030 ;
}
void ReverseByteOrder(unsigned long& val){
	val = 	(val & 0x000000FFul) << 030 |
			(val & 0x0000FF00ul) << 010 |
			(val & 0x00FF0000ul) >> 010 |
			(val & 0xFF000000ul) >> 030 ;
}
void ReverseByteOrder(unsigned long long& val){
	val =	(val & 0x00000000000000FFull) << 070 |
			(val & 0x000000000000FF00ull) << 050 |
			(val & 0x0000000000FF0000ull) << 030 |
			(val & 0x00000000FF000000ull) << 010 |
			(val & 0x000000FF00000000ull) >> 010 |
			(val & 0x0000FF0000000000ull) >> 030 |
			(val & 0x00FF000000000000ull) >> 050 |
			(val & 0xFF00000000000000ull) >> 070 ;
}
void ReverseByteOrder(void* const ptr, const unsigned int sz){
	for(int i = 0; i < sz - i - 1; i++){
		((char*)ptr)[i] ^= ((char*)ptr)[sz - i - 1];
		((char*)ptr)[sz - i - 1] ^= ((char*)ptr)[i];
		((char*)ptr)[i] ^= ((char*)ptr)[sz - i - 1];
	}
}
}