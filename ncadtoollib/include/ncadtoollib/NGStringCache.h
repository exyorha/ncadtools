#ifndef NCADTOOLIB_NGSTRINGCACHE_H
#define NCADTOOLIB_NGSTRINGCACHE_H

#include <ncadtoollib/NGCountedArray.h>

#include <string>
#include <atomic>
#include <unordered_map>

namespace ncadtoollib {
	class NGStream;

	class NGStringCacheEntry {
	public:
		uint32_t stringKey;
		uint32_t unknown2;
		std::string cachedString;
	};

	class NGStringCache {
	public:
		class CurrentScope {
		public:
			explicit CurrentScope(NGStringCache* cache);
			~CurrentScope();

			CurrentScope(CurrentScope& other) = delete;
			CurrentScope &operator =(CurrentScope& other) = delete;

		private:
			NGStringCache* m_prevCache;
		};

		static NGStringCache *swapCurrentCache(NGStringCache* newCache) noexcept;
		static NGStringCache* getCurrentCache();

		NGCountedArray<uint32_t, NGStringCacheEntry> cacheEntries;
	
		const std::string& get(uint32_t key) const;

		void rebuildCacheMap();

	private:
		static thread_local NGStringCache* m_currentCache;
		std::unordered_map<uint32_t, size_t> m_cacheMap;
	};

	NGStream& operator <<(NGStream& stream, const NGStringCacheEntry& obj);
	NGStream& operator >>(NGStream& stream, NGStringCacheEntry& obj);

	NGStream& operator <<(NGStream& stream, const NGStringCache& obj);
	NGStream& operator >>(NGStream& stream, NGStringCache& obj);
}

#endif
