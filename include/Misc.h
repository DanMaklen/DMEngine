#ifndef __20150711_MISC_H
#define __20150711_MISC_H

namespace DMEngine{
extern short& ReverseByteOrder(short&);
extern int& ReverseByteOrder(int&);
extern long& ReverseByteOrder(long&);
extern long long& ReverseByteOrder(long long&);
extern unsigned short& ReverseByteOrder(unsigned short&);
extern unsigned int& ReverseByteOrder(unsigned int&);
extern unsigned long& ReverseByteOrder(unsigned long&);
extern unsigned long long& ReverseByteOrder(unsigned long long&);
extern void ReverseByteOrder(void* const, const unsigned int);
}

#endif