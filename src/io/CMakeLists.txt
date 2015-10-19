project(ezi)

set(SRCS_IO
	input_reader_interface.h
	porter_stemmer.cpp
	porter_stemmer.h
	porter_stemmer_impl.c
	porter_stemmer_impl.h
	stemmer_interface.h
	text_input_reader.cpp
	text_input_reader.h
)

add_library(io ${SRCS_IO})
