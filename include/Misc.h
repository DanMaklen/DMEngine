#ifndef __20150711_MISC_H
#define __20150711_MISC_H

namespace DMEngine{
extern void ReverseByteOrder(short&);
extern void ReverseByteOrder(int&);
extern void ReverseByteOrder(long&);
extern void ReverseByteOrder(long long&);
extern void ReverseByteOrder(unsigned short&);
extern void ReverseByteOrder(unsigned int&);
extern void ReverseByteOrder(unsigned long&);
extern void ReverseByteOrder(unsigned long long&);
extern void ReverseByteOrder(void* const, const unsigned int);
}

#endif