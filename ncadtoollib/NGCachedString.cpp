#include <ncadtoollib/NGCachedString.h>
#include <ncadtoollib/NGStringCache.h>
#include <ncadtoollib/NGStream.h>

#include <stdexcept>

namespace ncadtoollib {
	const std::string& NGCachedString::string() const {
		return cache->get(stringKey);
	}

	NGStream& operator <<(NGStream& stream, const NGCachedString& obj) {
		if (obj.cache != NGStringCache::getCurrentCache())
			throw std::logic_error("attempted to serialize a NGCachedString from a non-current cache");

		return stream << obj.stringKey;
	}

	NGStream& operator >>(NGStream& stream, NGCachedString& obj) {
		obj.cache = NGStringCache::getCurrentCache();
		return stream >> obj.stringKey;
	}
}