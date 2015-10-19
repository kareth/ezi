#include "main/application.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "io/program_options_reader.h"

#include "io/input_reader_interface.h"
#include "io/text_input_reader.h"

#include "io/tokenizer_base.h"
#include "io/simple_tokenizer.h"

#include "io/stemmer_interface.h"
#include "io/porter_stemmer.h"

#include "db/document_database.h"

#include "engine/search_engine.h"

using namespace std;

Application::Application(int argc, char** argv)
	: argc(argc), argv(argv),
		programOptionsReaderPtr(new ProgramOptionsReader) {}

int Application::run() {
	shared_ptr<ProgramOptions> programOptionsPtr
		= programOptionsReaderPtr->read(argc, argv);
	if (programOptionsPtr == nullptr) return EXIT_SUCCESS;

	unique_ptr<InputReaderInterface> inputReaderPtr(new TextInputReader);
	unique_ptr<TokenizerBase> tokenizerPtr(new SimpleTokenizer);
	unique_ptr<StemmerInterface> stemmerPtr(new PorterStemmer);

	documentBuilderPtr= make_shared<DocumentBuilder>(
		move(inputReaderPtr), move(tokenizerPtr), move(stemmerPtr));

	ifstream keywordsFile(programOptionsPtr->keywordsInputFile);
	ifstream documentsFile(programOptionsPtr->documentsInputFile);
	DocumentDatabaseBuilder databaseBuilder(documentBuilderPtr);
	shared_ptr<DocumentDatabase> dbPtr
		= databaseBuilder.create(keywordsFile, documentsFile);
	if (dbPtr == nullptr) return EXIT_FAILURE;

	searchEnginePtr = unique_ptr<SearchEngine>(new SearchEngine(dbPtr));

///////////////

	for (auto str : programOptionsPtr->queries) {
		rank(str);
	}
	/*for (size_t i=0; i<1000; ++i) {
		rank("ml");
	}*/

	return EXIT_SUCCESS;
}

void Application::rank(const string& str) {
	typedef chrono::duration<int, micro> Duration;
	cout << endl << "query: " << str << endl;
	stringstream ss; ss << str;

	auto startTimePoint = chrono::steady_clock::now();

	auto vec = searchEnginePtr->rank(documentBuilderPtr->createOne(ss));

	auto endTimePoint = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<Duration>(endTimePoint - startTimePoint);

	cout << vec.size() << " results found in "
		<< duration.count() << " microseconds" << endl;
	for (auto el : vec) {
		cout << "\t"
			<< "sim(Q,D" << el.first->getId() << ") "
			<< el.second << endl;
	}
}
