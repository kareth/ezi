#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "io/input_file_reader_interface.h"
#include "io/text_file_input_reader.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Hello, ezi!" << endl;

	unique_ptr<InputFileReaderInterface> inputFileReaderPtr(new TextFileInputReader);
	shared_ptr<vector<string>> keywordsVectorPtr
		= inputFileReaderPtr->readKeywords("data/keywords.txt");
	if (keywordsVectorPtr == nullptr) return EXIT_FAILURE;

	cout << "keywords:" << endl;
	for (size_t i=0; i<keywordsVectorPtr->size(); ++i) {
		cout
			<< "'" << keywordsVectorPtr->at(i) << "'"
			<< endl;
	}

	shared_ptr<vector<vector<string>>> documentsVectorPtr
		= inputFileReaderPtr->readDocuments("data/documents.txt");
	if (documentsVectorPtr == nullptr) return EXIT_FAILURE;

	for (size_t i=0; i<documentsVectorPtr->size(); ++i) {
		cout << "document " << i << ":" << endl;
		for (size_t j=0; j<documentsVectorPtr->at(i).size(); ++j) {
			cout
				<< "'" << documentsVectorPtr->at(i)[j] << "'"
				<< endl;
		}
	}

	return EXIT_SUCCESS;
}
