#ifndef NCADTOOLIB_NGLOGBLOCK_H
#define NCADTOOLIB_NGLOGBLOCK_H

#include <ncadtoollib/NGLogBase.h>
#include <ncadtoollib/NGNonPrimitive.h>

namespace ncadtoollib {
	class NGStream;

	class NGLogBlock final : public NGLogBase {
	public:
		NGNonPrimitive nonPrimitive;
	};

	NGStream& operator <<(NGStream& stream, const NGLogBlock& obj);
	NGStream& operator >>(NGStream& stream, NGLogBlock& obj);
}

#endif
