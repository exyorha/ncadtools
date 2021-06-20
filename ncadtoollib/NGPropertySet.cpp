#include <ncadtoollib/NGPropertySet.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGPropertySet& obj) {
		stream << obj.properties;

		if (!obj.properties.empty())
			stream << obj.seed1 << obj.seed2;

		return stream;
	}

	NGStream& operator >>(NGStream& stream, NGPropertySet& obj) {
		stream >> obj.properties;

		if (!obj.properties.empty())
			stream >> obj.seed1 >> obj.seed2;

		return stream;
	}
}