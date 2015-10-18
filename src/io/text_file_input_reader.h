#ifndef IO_TEXT_FILE_INPUT_READER_H_
#define IO_TEXT_FILE_INPUT_READER_H_

#include "input_file_reader_interface.h"

#include <memory>
#include <string>
#include <vector>

class TextFileInputReader : public InputFileReaderInterface {
public:
	virtual std::shared_ptr<std::vector<std::string>>
		readKeywords(std::string filename);
	virtual std::shared_ptr<std::vector<std::vector<std::string>>>
		readDocuments(std::string filename);

private:
	std::string& trim(std::string&);
	std::vector<std::string> split(const std::string&, int delimiter(int) = ::isspace);
	std::string& normalize(std::string&);
};

#endif  // IO_TEXT_FILE_INPUT_READER_H_
