#ifndef NCADTOOLIB_NGCACHEDSTRING_H
#define NCADTOOLIB_NGCACHEDSTRING_H

#include <stdint.h>
#include <string>

namespace ncadtoollib {
	class NGStringCache;
	class NGStream;
	
	class NGCachedString {
	public:
		NGStringCache* cache;
		uint32_t stringKey;

		const std::string& string() const;
	};

	NGStream& operator <<(NGStream& stream, const NGCachedString& obj);
	NGStream& operator >>(NGStream& stream, NGCachedString& obj);
};

#endif
