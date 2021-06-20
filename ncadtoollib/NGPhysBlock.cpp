#include <ncadtoollib/NGPhysBlock.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGPhysBlockUnknownPart& obj) {
		return stream << static_cast<const NGObject&>(obj) << obj.unknown1;
	}

	NGStream& operator >>(NGStream& stream, NGPhysBlockUnknownPart& obj) {
		return stream >> static_cast<NGObject&>(obj) >> obj.unknown1;
	}

	NGStream& operator <<(NGStream& stream, const NGPhysBlock& obj) {
		return stream << static_cast<const NGBaseBlock&>(obj) << obj.unknown2 << obj.nonPrimitive;
	}

	NGStream& operator >>(NGStream& stream, NGPhysBlock& obj) {
		return stream >> static_cast<NGBaseBlock&>(obj) >> obj.unknown2 >> obj.nonPrimitive;
	}
}