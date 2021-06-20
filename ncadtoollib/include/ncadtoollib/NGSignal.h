#ifndef NCADTOOLIB_NGSIGNAL_H
#define NCADTOOLIB_NGSIGNAL_H

#include <ncadtoollib/NGObject.h>

namespace ncadtoollib {
	class NGStream;

	class NGSignal final : public NGObject {
	public:
		uint32_t unknown1;
		uint32_t unknown2;
	};

	NGStream& operator <<(NGStream& stream, const NGSignal& obj);
	NGStream& operator >>(NGStream& stream, NGSignal& obj);
}

#endif
