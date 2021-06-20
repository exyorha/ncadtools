#include <ncadtoollib/NGWire.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGWire& obj) {
		return stream << static_cast<const NGObject&>(obj) << obj.internalConnectionId << obj.networkId;
	}

	NGStream& operator >>(NGStream& stream, NGWire& obj) {
		return stream >> static_cast<NGObject&>(obj) >> obj.internalConnectionId >> obj.networkId;
	}
}
