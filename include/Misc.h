#ifndef __20150711_MISC_H
#define __20150711_MISC_H

namespace DMEngine{
extern short ReverseByteOrder(const short);
extern int ReverseByteOrder(const int);
extern long ReverseByteOrder(const long);
extern long long ReverseByteOrder(const long long);
extern unsigned short ReverseByteOrder(const unsigned short);
extern unsigned int ReverseByteOrder(const unsigned int);
extern unsigned long ReverseByteOrder(const unsigned long);
extern unsigned long long ReverseByteOrder(const unsigned long long);
extern void ReverseByteOrder(void* const, const unsigned int);
}

#endif