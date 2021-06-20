#include <ncadtoollib/NGLogBlock.h>

namespace ncadtoollib {

	NGStream& operator <<(NGStream& stream, const NGLogBlock& obj) {
		return stream << static_cast<const NGLogBase&>(obj) << obj.nonPrimitive;
	}

	NGStream& operator >>(NGStream& stream, NGLogBlock& obj) {
		return stream >> static_cast<NGLogBase&>(obj) >> obj.nonPrimitive;
	}
}