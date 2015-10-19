#ifndef SRC_IO_PROGRAM_OPTIONS_READER_H_
#define SRC_IO_PROGRAM_OPTIONS_READER_H_

#include "io/program_options_reader_interface.h"

#include <memory>
#include <string>

#include "common/program_options.h"

class ProgramOptionsReader : public ProgramOptionsReaderInterface {
public:
	virtual std::shared_ptr<ProgramOptions> read(int argc, char* argv[]);

private:
	static const std::string DEFAULT_KEYWORDS_FILE;
	static const std::string DEFAULT_DOCUMENTS_FILE;
};

#endif  // SRC_IO_PROGRAM_OPTIONS_READER_H_
