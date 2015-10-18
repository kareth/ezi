project(ezi)

set(SRCS_IO
	input_file_reader_interface.h
	porter_stemmer.cpp
	porter_stemmer.h
	porter_stemmer_impl.c
	porter_stemmer_impl.h
	stemmer_interface.h
	text_file_input_reader.cpp
	text_file_input_reader.h
)

add_library(io ${SRCS_IO})
