#ifndef SRC_COMMON_PROGRAM_OPTIONS_H_
#define SRC_COMMON_PROGRAM_OPTIONS_H_

#include <string>
#include <vector>

struct ProgramOptions {
	std::string keywordsInputFile;
	std::string documentsInputFile;
	std::vector<std::string> queries;
	std::vector<std::string> expandings;
	bool verbose;
};

#endif  // SRC_COMMON_PROGRAM_OPTIONS_H_
