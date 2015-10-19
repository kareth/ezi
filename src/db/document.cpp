#include "db/document.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

Document::Document(size_t id, shared_ptr<vector<string>> stemmedContentPtr)
	: id(id), stemmedContentPtr(stemmedContentPtr) {}

Document::Document(size_t id)
	: id(id), stemmedContentPtr(make_shared<vector<string>>()) {}

DocumentBuilder::DocumentBuilder(unique_ptr<InputReaderInterface> inputReaderPtr,
		unique_ptr<StemmerInterface> stemmerPtr)
	: inputReaderPtr(move(inputReaderPtr)), stemmerPtr(move(stemmerPtr)) {
}

shared_ptr<Document> DocumentBuilder::createOne(istream& is, size_t id) {
	shared_ptr<Document> documentPtr = make_shared<Document>(id);

	try {
		shared_ptr<vector<string>> words = inputReaderPtr->read(is)->at(0);
		for (size_t i=0; i<words->size(); ++i) {
			documentPtr->getStemmedContentPtr()->push_back(stemmerPtr->stem(words->at(i)));
		}
	} catch(out_of_range& e) {
		cerr << e.what() << endl;
	}

	return documentPtr;
}

shared_ptr<vector<shared_ptr<Document>>> DocumentBuilder::createMany(istream& is) {
	shared_ptr<vector<shared_ptr<Document>>> documentPtrs
		= make_shared<vector<shared_ptr<Document>>>();

	shared_ptr<vector<shared_ptr<vector<string>>>> words
		= inputReaderPtr->read(is);

	for (size_t i=0; i<words->size(); ++i) {
		shared_ptr<Document> documentPtr = make_shared<Document>(i+1);

		for (size_t j=0; j<words->at(i)->size(); ++j) {
			documentPtr->getStemmedContentPtr()
				->push_back(stemmerPtr->stem(words->at(i)->at(j)));
		}

		documentPtrs->push_back(documentPtr);
	}

	return documentPtrs;
}
