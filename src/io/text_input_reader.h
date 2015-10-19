#ifndef IO_TEXT_INPUT_READER_H_
#define IO_TEXT_INPUT_READER_H_

#include "input_reader_interface.h"

#include <string>
#include <vector>

class TextInputReader : public InputReaderInterface {
public:
	virtual std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>>
		read(std::istream&);

private:
	std::string& trim(std::string&);
	std::vector<std::string> split(const std::string&, int delimiter(int) = ::isspace);
	std::string& normalize(std::string&);
};

#endif  // IO_TEXT_INPUT_READER_H_
