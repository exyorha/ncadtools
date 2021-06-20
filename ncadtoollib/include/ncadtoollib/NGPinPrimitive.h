#ifndef NCADTOOLIB_NGPINPRIMITIVE_H
#define NCADTOOLIB_NGPINPRIMITIVE_H

#include <ncadtoollib/NGPin.h>

namespace ncadtoollib {
	class NGStream;

	class NGPinPrimitive final : public NGPin {
	public:
		uint8_t unknown6;
		uint8_t unknown7;
	};

	NGStream& operator <<(NGStream& stream, const NGPinPrimitive& obj);
	NGStream& operator >>(NGStream& stream, NGPinPrimitive& obj);
}

#endif
