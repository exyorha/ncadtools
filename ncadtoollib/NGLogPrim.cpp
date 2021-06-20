#include <ncadtoollib/NGLogPrim.h>

namespace ncadtoollib {

	NGStream& operator <<(NGStream& stream, const NGLogPrim& obj) {
		return stream << static_cast<const NGLogBase&>(obj) << obj.primitive;
	}

	NGStream& operator >>(NGStream& stream, NGLogPrim& obj) {
		return stream >> static_cast<NGLogBase&>(obj) >> obj.primitive;
	}
}