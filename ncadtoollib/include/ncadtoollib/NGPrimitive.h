#ifndef NCADTOOLIB_NGPRIMITIVE_H
#define NCADTOOLIB_NGPRIMITIVE_H

#include <ncadtoollib/NGCountedArray.h>
#include <ncadtoollib/NGPinPrimitive.h>

namespace ncadtoollib {
	class NGStream;

	class NGPrimitive {
	public:
		uint8_t unknown1;
		NGCountedArray<uint16_t, NGPinPrimitive> pins;
	};

	NGStream& operator <<(NGStream& stream, const NGPrimitive& obj);
	NGStream& operator >>(NGStream& stream, NGPrimitive& obj);
}

#endif
