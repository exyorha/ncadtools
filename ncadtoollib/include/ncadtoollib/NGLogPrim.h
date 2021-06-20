#ifndef NCADTOOLIB_NGLOGPRIM_H
#define NCADTOOLIB_NGLOGPRIM_H

#include <ncadtoollib/NGLogBase.h>
#include <ncadtoollib/NGPrimitive.h>

namespace ncadtoollib {
	class NGLogPrim final : public NGLogBase {
	public:
		NGPrimitive primitive;
	};

	NGStream& operator <<(NGStream& stream, const NGLogPrim& obj);
	NGStream& operator >>(NGStream& stream, NGLogPrim& obj);
}

#endif
