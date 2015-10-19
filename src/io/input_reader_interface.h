#ifndef SRC_IO_INPUT_READER_INTERFACE_H_
#define SRC_IO_INPUT_READER_INTERFACE_H_

#include <fstream>
#include <memory>
#include <string>
#include <vector>

class InputReaderInterface {
public:
	virtual std::shared_ptr<std::vector<std::pair<std::string, std::vector<std::string>>>>
		read(std::istream&) = 0;
};

#endif  // SRC_IO_INPUT_READER_INTERFACE_H_
