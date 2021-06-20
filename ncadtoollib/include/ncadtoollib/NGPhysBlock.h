#ifndef NCADTOOLIB_NGPHYSBLOCK_H
#define NCADTOOLIB_NGPHYSBLOCK_H

#include <ncadtoollib/NGBaseBlock.h>
#include <ncadtoollib/NGCountedArray.h>
#include <ncadtoollib/NGNonPrimitive.h>

namespace ncadtoollib {
	class NGStream;

	class NGPhysBlockUnknownPart final : public NGObject {
	public:
		uint32_t unknown1;
	};

	class NGPhysBlock final : public NGBaseBlock {
	public:
		NGCountedArray<uint16_t, NGPhysBlockUnknownPart> unknown2;
		NGNonPrimitive nonPrimitive;
	};

	NGStream& operator <<(NGStream& stream, const NGPhysBlockUnknownPart& obj);
	NGStream& operator >>(NGStream& stream, NGPhysBlockUnknownPart& obj);

	NGStream& operator <<(NGStream& stream, const NGPhysBlock& obj);
	NGStream& operator >>(NGStream& stream, NGPhysBlock& obj);
}

#endif
