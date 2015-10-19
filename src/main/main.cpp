#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "io/input_reader_interface.h"
#include "io/text_input_reader.h"

#include "io/stemmer_interface.h"
#include "io/porter_stemmer.h"

#include "db/document_database.h"

#include "engine/search_engine.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Hello, ezi!" << endl;

	unique_ptr<InputReaderInterface> inputReaderPtr(new TextInputReader);
	unique_ptr<StemmerInterface> stemmerPtr(new PorterStemmer);

	shared_ptr<DocumentBuilder> documentBuilder
		= make_shared<DocumentBuilder>(move(inputReaderPtr), move(stemmerPtr));

	ifstream keywordsFile("data/keywords.txt");
	ifstream documentsFile("data/documents.txt");
	DocumentDatabaseBuilder databaseBuilder(documentBuilder);
	shared_ptr<DocumentDatabase> dbPtr
		= databaseBuilder.create(keywordsFile, documentsFile);
	if (dbPtr == nullptr) return EXIT_FAILURE;

	SearchEngine engine(dbPtr);

///////////

	auto rank = [&](const string& str) {
		// cout << "query: " << str << endl;
		stringstream ss; ss << str;
		engine.rank(documentBuilder->createOne(ss));
	};

	/*for (size_t i=0; i<1000; i++) {
		rank("ml");
	}*/
	rank("information retrieval");
	rank("agency");

	return EXIT_SUCCESS;
}
