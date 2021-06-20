#include <stdio.h>

#include <vector>
#include <string>
#include <filesystem>

#if defined(_WIN32)
#include "windowsStringConversions.h"
#endif

#include <mio/mmap.hpp>

#include <ncadtoollib/NGInputStream.h>
#include <ncadtoollib/NGDFile.h>

#include <fstream>

#include "NGDToVerilogConverter.h"

static int utf8main(int argc, const char** argv) {
	std::ios::sync_with_stdio(false);

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <INPUT NGD FILE> <OUTPUT VERILOG FILE>\n", argv[0]);
		return 1;
	}

	try {
		ncadtoollib::NGDFile ngd;

		{
			mio::ummap_source mapping(argv[1]);

			ncadtoollib::NGInputStream stream(mapping.data(), mapping.size());

			stream >> ngd;
		}

		std::filesystem::path outputFilename;
#if defined(_WIN32)
		outputFilename = utf8StringToWideString(argv[2]);
#else
		outputFilename = argv[2];
#endif

		std::ofstream output;
		output.exceptions(std::ios::failbit | std::ios::badbit | std::ios::eofbit);
		output.open(outputFilename, std::ios::out | std::ios::trunc | std::ios::binary);

		NGDToVerilogConverter converter(ngd, output);
		converter.setInputFilename(argv[1]);
		
		converter.convert();
		
		return 0;
	}
	catch (const std::exception& e) {
		fprintf(stderr, "An error ocurred during processing: %s\n", e.what());
		return 1;
	}
}

#if defined(_WIN32)
int wmain(int argc, wchar_t** argv) {
	std::vector<std::string> strings;
	strings.reserve(argc);

	for (int index = 0; index < argc; index++) {
		strings.emplace_back(wideStringToUtf8String(argv[index]));
	}

	std::vector<const char*> stringPointers;
	stringPointers.reserve(static_cast<size_t>(argc) + 1);

	for (const auto& string : strings) {
		stringPointers.emplace_back(string.c_str());
	}

	stringPointers.emplace_back(nullptr);

	return utf8main(stringPointers.size() - 1, stringPointers.data());
}
#else
int main(int argc, char** argv) {
	return utf8main(argc, argv);
}
#endif
