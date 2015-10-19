project(ezi)

set(SRCS_IO
	input_reader_interface.h
	porter_stemmer.cpp
	porter_stemmer.h
	porter_stemmer_impl.c
	porter_stemmer_impl.h
	program_options_reader_interface.h
	program_options_reader.cpp
	program_options_reader.h
	simple_tokenizer.cpp
	simple_tokenizer.h
	stemmer_interface.h
	text_input_reader.cpp
	text_input_reader.h
	tokenizer_base.cpp
	tokenizer_base.h
)

add_library(io ${SRCS_IO})
