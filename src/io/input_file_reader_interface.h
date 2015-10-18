#ifndef SRC_IO_INPUT_FILE_READER_INTERFACE_H_
#define SRC_IO_INPUT_FILE_READER_INTERFACE_H_

#include <memory>
#include <string>
#include <vector>

class InputFileReaderInterface {
public:
	virtual std::shared_ptr<std::vector<std::string>>
		readKeywords(std::string filename) = 0;
	virtual std::shared_ptr<std::vector<std::vector<std::string>>>
		readDocuments(std::string filename) = 0;
};

#endif  // SRC_IO_INPUT_FILE_READER_INTERFACE_H_
