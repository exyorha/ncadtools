#include <ncadtoollib/NGSignal.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGSignal& obj) {
		return stream << static_cast<const NGObject&>(obj) << obj.unknown1 << obj.unknown2;
	}

	NGStream& operator >>(NGStream& stream, NGSignal& obj) {
		return stream >> static_cast<NGObject&>(obj) >> obj.unknown1 >> obj.unknown2;
	}
}