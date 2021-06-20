#include <ncadtoollib/NGNetwork.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGNetwork& obj) {
		return stream << obj.properties << obj.unknown1 << obj.unknown2;
	}

	NGStream& operator >>(NGStream& stream, NGNetwork& obj) {
		return stream >> obj.properties >> obj.unknown1 >> obj.unknown2;
	}
}