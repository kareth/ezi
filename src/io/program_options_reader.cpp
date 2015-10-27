#include "io/program_options_reader.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

const string ProgramOptionsReader::DEFAULT_KEYWORDS_FILE = "data/keywords.txt";
const string ProgramOptionsReader::DEFAULT_DOCUMENTS_FILE = "data/documents.txt";

shared_ptr<ProgramOptions> ProgramOptionsReader::read(int argc, char* argv[]) {
	shared_ptr<ProgramOptions> programOptionsPtr = make_shared<ProgramOptions>();

	po::options_description optionsDescription("Allowed options");
	optionsDescription.add_options()
		("help,h",
			"produce help message")
		("keywords",
			po::value<string>(&programOptionsPtr->keywordsInputFile)
				->default_value(DEFAULT_KEYWORDS_FILE),
			"keywords file")
		("documents",
			po::value<string>(&programOptionsPtr->documentsInputFile)
				->default_value(DEFAULT_DOCUMENTS_FILE),
			"documents file")
		("query",
			po::value<vector<string>>(&programOptionsPtr->queries)->composing(),
			"query")
		("expand",
			po::value<vector<string>>(&programOptionsPtr->expandings)->composing(),
			"expand query");

	try {
		po::variables_map variablesMap;
		po::store(po::parse_command_line(argc, argv, optionsDescription), variablesMap);
		po::notify(variablesMap);

		if (variablesMap.count("help")) {
			cout << optionsDescription << endl;
			return nullptr;
		}

		programOptionsPtr->verbose = variablesMap.count("verbose");

	} catch (po::error& e) {
		cerr << e.what() << endl;
		cout << optionsDescription << endl;
		return nullptr;
	}

	return programOptionsPtr;
}
