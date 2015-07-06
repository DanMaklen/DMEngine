#ifndef __20150703_IMAGE_H
#define __20150703_IMAGE_H

class Image{
public:
	enum struct Type{
		Null,
		PNG,									//PNG
		Count
	};
public:
	static char* Parse(const char* const, unsigned int&, unsigned int&, const Type = Type::Null);
};

#endif