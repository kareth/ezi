#ifndef SRC_IO_PROGRAM_OPTIONS_READER_INTERFACE_H_
#define SRC_IO_PROGRAM_OPTIONS_READER_INTERFACE_H_

#include <memory>

#include "common/program_options.h"

class ProgramOptionsReaderInterface {
public:
	virtual std::shared_ptr<ProgramOptions> read(int argc, char* argv[]) = 0;
};

#endif  // SRC_IO_PROGRAM_OPTIONS_READER_INTERFACE_H_
