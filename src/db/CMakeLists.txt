project(ezi)

set(SRCS_DB
	document.cpp
	document.h
	document_database.cpp
	document_database.h
)

add_library(db ${SRCS_DB})
