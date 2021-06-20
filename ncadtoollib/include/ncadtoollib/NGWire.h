#ifndef NCADTOOLIB_NGWIRE_H
#define NCADTOOLIB_NGWIRE_H

#include <ncadtoollib/NGObject.h>

namespace ncadtoollib {
	class NGStream;

	class NGWire final : public NGObject {
	public:
		uint32_t internalConnectionId;
		uint32_t networkId;
	};

	NGStream& operator <<(NGStream& stream, const NGWire& obj);
	NGStream& operator >>(NGStream& stream, NGWire& obj);
}

#endif
