#include <ncadtoollib/NGBaseBlock.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {

	NGStream& operator <<(NGStream& stream, const NGBaseBlock& obj) {
		return stream << static_cast<const NGObject &>(obj) << obj.edifSeqnum << obj.thisModuleId << obj.parentModuleId << obj.wires;
	}

	NGStream& operator >>(NGStream& stream, NGBaseBlock& obj) {
		return stream >> static_cast<NGObject&>(obj) >> obj.edifSeqnum >> obj.thisModuleId >> obj.parentModuleId >> obj.wires;
	}
}
