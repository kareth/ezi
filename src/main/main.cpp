#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "io/program_options_reader.h"

#include "io/input_reader_interface.h"
#include "io/text_input_reader.h"

#include "io/stemmer_interface.h"
#include "io/porter_stemmer.h"

#include "db/document_database.h"

#include "engine/search_engine.h"

using namespace std;

int main(int argc, char* argv[]) {

	ProgramOptionsReader optionsReader;
	shared_ptr<ProgramOptions> programOptionsPtr = optionsReader.read(argc, argv);
	if (programOptionsPtr == nullptr) return EXIT_SUCCESS;

	unique_ptr<InputReaderInterface> inputReaderPtr(new TextInputReader);
	unique_ptr<StemmerInterface> stemmerPtr(new PorterStemmer);

	shared_ptr<DocumentBuilder> documentBuilder
		= make_shared<DocumentBuilder>(move(inputReaderPtr), move(stemmerPtr));

	ifstream keywordsFile(programOptionsPtr->keywordsInputFile);
	ifstream documentsFile(programOptionsPtr->documentsInputFile);
	DocumentDatabaseBuilder databaseBuilder(documentBuilder);
	shared_ptr<DocumentDatabase> dbPtr
		= databaseBuilder.create(keywordsFile, documentsFile);
	if (dbPtr == nullptr) return EXIT_FAILURE;

	SearchEngine engine(dbPtr);

///////////

	auto rank = [&](const string& str) {
		cout << endl;
		cout << "query: " << str << endl;
		stringstream ss; ss << str;
		auto vec = engine.rank(documentBuilder->createOne(ss));
		cout << vec.size() << " results found" << endl;
		for (auto el : vec) {
			cout << "\t"
				<< "sim(Q,D" << el.first->getId() << ") "
				<< el.second << endl;
		}
	};

	for (auto str : programOptionsPtr->queries) {
		rank(str);
	}

	return EXIT_SUCCESS;
}
