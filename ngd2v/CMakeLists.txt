add_executable(ngd2v
	main.cpp
	NGDToVerilogConverter.cpp
	NGDToVerilogConverter.h
)

if(WIN32)
	target_sources(ngd2v PRIVATE 
		windowsStringConversions.cpp
		windowsStringConversions.h
	)
	target_compile_definitions(ngd2v PRIVATE -DWIN32_LEAN_AND_MEAN -DNOMINMAX -DUNICODE -D_UNICODE)
endif()

target_link_libraries(ngd2v PRIVATE ncadtoollib mio::mio)
set_target_properties(ngd2v PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE)
