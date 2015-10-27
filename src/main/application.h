#ifndef SRC_MAIN_APPLICATION_H_
#define SRC_MAIN_APPLICATION_H_

#include <memory>
#include <string>

#include "io/program_options_reader_interface.h"
#include "db/document_database.h"
#include "engine/search_engine.h"
#include "engine/query_expander.h"

class Application {
public:
	Application(int argc, char* argv[]);
	int run();

private:
	void rank(const std::string&);
	void expand(const std::string&);

	int argc;
	char** argv;

	std::unique_ptr<ProgramOptionsReaderInterface> programOptionsReaderPtr;
	std::shared_ptr<DocumentBuilder> documentBuilderPtr;
	std::unique_ptr<SearchEngine> searchEnginePtr;
	std::unique_ptr<QueryExpander> queryExpanderPtr;
};

#endif  // SRC_MAIN_APPLICATION_H_
