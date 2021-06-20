#include <ncadtoollib/NGPin.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGPin& obj) {
		return stream
			<< static_cast<const NGObject&>(obj)
			<< obj.externalConnectionId
			<< obj.internalConnectionId
			<< obj.unknown3
			<< obj.direction
			<< obj.unknown5;
	}

	NGStream& operator >>(NGStream& stream, NGPin& obj) {
		return stream
			>> static_cast<NGObject&>(obj)
			>> obj.externalConnectionId
			>> obj.internalConnectionId
			>> obj.unknown3
			>> obj.direction
			>> obj.unknown5;
	}
}
