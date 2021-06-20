#ifndef NCADTOOLIB_NGNONPRIMITIVE_H
#define NCADTOOLIB_NGNONPRIMITIVE_H

#include <ncadtoollib/NGCountedArray.h>
#include <ncadtoollib/NGPin.h>

namespace ncadtoollib {
	class NGNonPrimitive {
	public:
		NGCountedArray<uint16_t, NGPin> pins;
	};

	NGStream& operator <<(NGStream& stream, const NGNonPrimitive& obj);
	NGStream& operator >>(NGStream& stream, NGNonPrimitive& obj);
}

#endif
