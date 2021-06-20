#ifndef NCADTOOLIB_NGLOGBASE_H
#define NCADTOOLIB_NGLOGBASE_H

#include <ncadtoollib/NGBaseBlock.h>

namespace ncadtoollib {
	class NGStream;

	class NGLogBase : public NGBaseBlock {
	public:
		uint32_t unknown3_1;
		uint8_t  unknown3_2;
	};

	NGStream& operator <<(NGStream& stream, const NGLogBase& obj);
	NGStream& operator >>(NGStream& stream, NGLogBase& obj);
}

#endif
