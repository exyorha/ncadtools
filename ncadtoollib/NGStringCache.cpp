#include <ncadtoollib/NGStream.h>
#include <ncadtoollib/NGStringCache.h>

#include <stdexcept>

namespace ncadtoollib {
	thread_local NGStringCache* NGStringCache::m_currentCache;

	NGStringCache::CurrentScope::CurrentScope(NGStringCache* cache) {
		m_prevCache = NGStringCache::swapCurrentCache(cache);
	}

	NGStringCache::CurrentScope::~CurrentScope() {
		NGStringCache::swapCurrentCache(m_prevCache);
	}

	NGStringCache* NGStringCache::swapCurrentCache(NGStringCache* newCache) noexcept {
		auto prevCache = m_currentCache;
		m_currentCache = newCache;

		return prevCache;
	}

	NGStringCache* NGStringCache::getCurrentCache() {
		if (!m_currentCache)
			throw std::logic_error("no current NGStringCache");

		return m_currentCache;
	}

	const std::string& NGStringCache::get(uint32_t key) const {
		auto it = m_cacheMap.find(key);
		if (it == m_cacheMap.end())
			throw std::runtime_error("string not found with the key: " + std::to_string(key));

		return cacheEntries[it->second].cachedString;
	}

	void NGStringCache::rebuildCacheMap() {
		m_cacheMap.clear();
		m_cacheMap.reserve(cacheEntries.size());

		for (size_t index = 0, size = cacheEntries.size(); index < size; index++) {
			m_cacheMap.emplace(cacheEntries[index].stringKey, index);
		}
	}

	NGStream& operator <<(NGStream& stream, const NGStringCache& obj) {
		return stream << obj.cacheEntries;
	}

	NGStream& operator >>(NGStream& stream, NGStringCache& obj) {
		stream >> obj.cacheEntries;
		obj.rebuildCacheMap();
		return stream;
	}

	NGStream& operator <<(NGStream& stream, const NGStringCacheEntry& obj) {
		return stream << obj.stringKey << obj.unknown2 << obj.cachedString;
	}

	NGStream& operator >>(NGStream& stream, NGStringCacheEntry& obj) {
		return stream >> obj.stringKey >> obj.unknown2 >> obj.cachedString;
	}
}
