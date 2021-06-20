#ifndef NCADTOOLIB_NGPIN_H
#define NCADTOOLIB_NGPIN_H

#include <ncadtoollib/NGObject.h>

namespace ncadtoollib {
	class NGStream;

	class NGPin : public NGObject {
	public:
		uint32_t externalConnectionId;
		uint32_t internalConnectionId;
		uint32_t unknown3;
		uint8_t  direction;
		uint8_t  unknown5;
	};

	NGStream& operator <<(NGStream& stream, const NGPin& obj);
	NGStream& operator >>(NGStream& stream, NGPin& obj);
}

#endif
