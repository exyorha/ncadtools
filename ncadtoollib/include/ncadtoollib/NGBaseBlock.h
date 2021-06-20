#ifndef NCADTOOLIB_NGBASEBLOCK_H
#define NCADTOOLIB_NGBASEBLOCK_H

#include <stdint.h>

#include <ncadtoollib/NGObject.h>
#include <ncadtoollib/NGCountedArray.h>
#include <ncadtoollib/NGWire.h>

namespace ncadtoollib {
	class NGStream;

	class NGBaseBlock : public NGObject {
	public:
		uint32_t edifSeqnum;

		uint32_t thisModuleId;
		uint32_t parentModuleId;

		NGCountedArray<uint32_t, NGWire> wires;
	};

	NGStream& operator <<(NGStream& stream, const NGBaseBlock& obj);
	NGStream& operator >>(NGStream& stream, NGBaseBlock& obj);
}

#endif
