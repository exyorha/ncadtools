#ifndef NCADTOOLIB_NGPROPERTYSET_H
#define NCADTOOLIB_NGPROPERTYSET_H

#include <ncadtoollib/NGCountedArray.h>
#include <ncadtoollib/NGTaggedUnion.h>
#include <ncadtoollib/NGProperty.h>

namespace ncadtoollib {
	class NGStream;

	class NGPropertySet {
	public:
		NGCountedArray<uint16_t,
			NGTaggedUnion<uint8_t,
				NGProperty,
				NGPropertyInteger,
				NGPropertyFloat,
				NGPropertyString,
				NGPropertyObject,
				NGPropertyTiming,
				NGPropertyPinref,
				NGPropertyParameter,
				NGPropertyTimingString>> properties;

		uint16_t seed1;
		uint16_t seed2;
	};

	NGStream& operator <<(NGStream& stream, const NGPropertySet& obj);
	NGStream& operator >>(NGStream& stream, NGPropertySet& obj);
}

#endif
