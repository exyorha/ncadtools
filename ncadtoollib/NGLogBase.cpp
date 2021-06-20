#include <ncadtoollib/NGLogBase.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGLogBase& obj) {
		return stream << static_cast<const NGBaseBlock&>(obj) << obj.unknown3_1 << obj.unknown3_2;
	}

	NGStream& operator >>(NGStream& stream, NGLogBase& obj) {
		return stream >> static_cast<NGBaseBlock&>(obj) >> obj.unknown3_1 >> obj.unknown3_2;
	}
}