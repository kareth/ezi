project(ezi)

set(SRCS_ENGINE
	search_engine.cpp
	search_engine.h
	query_expander.cpp
	query_expander.h
)

set (LIBS_ENGINE
	${LIBWORDNET_LIBRARIES}
)

add_library(engine ${SRCS_ENGINE})
target_link_libraries(engine ${LIBS_ENGINE})
