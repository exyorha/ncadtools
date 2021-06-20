#ifndef NCADTOOLIB_NGNETWORK_H
#define NCADTOOLIB_NGNETWORK_H

#include <ncadtoollib/NGPropertySet.h>

namespace ncadtoollib {
	class NGStream;

	class NGNetwork {
	public:
		NGPropertySet properties;
		uint32_t unknown1;
		uint32_t unknown2;
	};

	NGStream& operator <<(NGStream& stream, const NGNetwork& obj);
	NGStream& operator >>(NGStream& stream, NGNetwork& obj);
}

#endif
