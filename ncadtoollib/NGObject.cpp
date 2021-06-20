#include <ncadtoollib/NGObject.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGObject& obj) {
		return stream << obj.objectName << obj.properties;
	}

	NGStream& operator >>(NGStream& stream, NGObject& obj) {
		return stream >> obj.objectName >> obj.properties;
	}
}
