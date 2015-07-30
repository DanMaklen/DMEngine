#include <Misc.h>

namespace DMEngine{
short ReverseByteOrder(const short val){
	return  (val & 0x00FFu) << 010 |
			(val & 0xFF00u) >> 010 ;
}
int ReverseByteOrder(const int val){
	return 	(val & 0x000000FFu) << 030 |
			(val & 0x0000FF00u) << 010 |
			(val & 0x00FF0000u) >> 010 |
			(val & 0xFF000000u) >> 030 ;
}
long ReverseByteOrder(const long val){
	return  (val & 0x000000FFul) << 030 |
			(val & 0x0000FF00ul) << 010 |
			(val & 0x00FF0000ul) >> 010 |
			(val & 0xFF000000ul) >> 030 ;
}
long long ReverseByteOrder(const long long val){
	return  (val & 0x00000000000000FFull) << 070 |
			(val & 0x000000000000FF00ull) << 050 |
			(val & 0x0000000000FF0000ull) << 030 |
			(val & 0x00000000FF000000ull) << 010 |
			(val & 0x000000FF00000000ull) >> 010 |
			(val & 0x0000FF0000000000ull) >> 030 |
			(val & 0x00FF000000000000ull) >> 050 |
			(val & 0xFF00000000000000ull) >> 070 ;
}
unsigned short ReverseByteOrder(const unsigned short val){
	return 	(val & 0x00FFu) << 010 |
			(val & 0xFF00u) >> 010 ;
}
unsigned int ReverseByteOrder(const unsigned int val){
	return 	(val & 0x000000FFu) << 030 |
			(val & 0x0000FF00u) << 010 |
			(val & 0x00FF0000u) >> 010 |
			(val & 0xFF000000u) >> 030 ;
}
unsigned long ReverseByteOrder(const unsigned long val){
	return 	(val & 0x000000FFul) << 030 |
			(val & 0x0000FF00ul) << 010 |
			(val & 0x00FF0000ul) >> 010 |
			(val & 0xFF000000ul) >> 030 ;
}
unsigned long long ReverseByteOrder(const unsigned long long val){
	return  (val & 0x00000000000000FFull) << 070 |
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