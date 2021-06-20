#include <ncadtoollib/NGPinPrimitive.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGPinPrimitive& obj) {
		return stream << static_cast<const NGPin&>(obj) << obj.unknown6 << obj.unknown7;
	}

	NGStream& operator >>(NGStream& stream, NGPinPrimitive& obj) {
		return stream >> static_cast<NGPin&>(obj) >> obj.unknown6 >> obj.unknown7;
	}
}