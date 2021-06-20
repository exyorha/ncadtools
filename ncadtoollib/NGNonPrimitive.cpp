#include <ncadtoollib/NGNonPrimitive.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGNonPrimitive& obj) {
		return stream << obj.pins;
	}

	NGStream& operator >>(NGStream& stream, NGNonPrimitive& obj) {
		return stream >> obj.pins;
	}
}
