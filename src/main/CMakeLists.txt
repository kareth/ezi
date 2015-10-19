project(tsp)

set(SRCS_MAIN
	application.cpp
	application.h
	main.cpp
)

set(LIBS_MAIN
	db
	engine
	io
	${Boost_PROGRAM_OPTIONS_LIBRARY}
)

add_executable(main ${SRCS_MAIN})
target_link_libraries(main ${LIBS_MAIN})
