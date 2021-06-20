#include <ncadtoollib/NGPrimitive.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGPrimitive& obj) {
		return stream << obj.unknown1 << obj.pins;
	}

	NGStream& operator >>(NGStream& stream, NGPrimitive& obj) {
		return stream >> obj.unknown1 >> obj.pins;
	}
}

