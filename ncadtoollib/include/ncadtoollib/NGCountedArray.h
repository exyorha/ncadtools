#ifndef NCADTOOLIB_NGCOUNTEDARRAY_H
#define NCADTOOLIB_NGCOUNTEDARRAY_H

#include <vector>

namespace ncadtoollib {
	class NGStream;

	template<typename CountType, typename DataType>
	class NGCountedArray final : public std::vector<DataType> {

	};

	template<typename CountType, typename DataType>
	NGStream& operator <<(NGStream& stream, const NGCountedArray<CountType, DataType>& obj) {
		stream << static_cast<CountType>(obj.size());
		stream << static_cast<const std::vector<DataType> &>(obj);
		return stream;
	}

	template<typename CountType, typename DataType>
	NGStream& operator >>(NGStream& stream, NGCountedArray<CountType, DataType>& obj) {
		CountType count;
		stream >> count;
		obj.resize(count);

		stream >> static_cast<std::vector<DataType>&>(obj);

		return stream;
	}
}

#endif
