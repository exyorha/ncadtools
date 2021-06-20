#ifndef NCADTOOLIB_NG_OBJECT_H
#define NCADTOOLIB_NG_OBJECT_H

#include <ncadtoollib/NGCachedString.h>
#include <ncadtoollib/NGPropertySet.h>

namespace ncadtoollib {
	class NGStream;

	class NGObject {
	public:
		NGCachedString objectName;
		NGPropertySet properties;
	};

	NGStream& operator <<(NGStream& stream, const NGObject& obj);
	NGStream& operator >>(NGStream& stream, NGObject& obj);
}

#endif
