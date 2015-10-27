#include "db/document.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

Document::Document(size_t id)
	: id(id) {}

DocumentBuilder::DocumentBuilder(unique_ptr<InputReaderInterface> inputReaderPtr,
		unique_ptr<TokenizerBase> tokenizerPtr,
		unique_ptr<StemmerInterface> stemmerPtr)
	: inputReaderPtr(move(inputReaderPtr)),
		tokenizerPtr(move(tokenizerPtr)),
		stemmerPtr(move(stemmerPtr)) {
}

shared_ptr<Document> DocumentBuilder::createOne(istream& is, size_t id) {
	auto documentPtr = make_shared<Document>(id);

	try {
		auto contents = inputReaderPtr->read(is);
		updateDocument(contents->at(0), documentPtr);
	} catch(out_of_range& e) {
		cerr << e.what() << endl;
	}

	return documentPtr;
}

shared_ptr<vector<shared_ptr<Document>>> DocumentBuilder::createMany(istream& is) {
	auto documentPtrs = make_shared<vector<shared_ptr<Document>>>();

	auto contentsPtr = inputReaderPtr->read(is);

	for (size_t i=0; i<contentsPtr->size(); ++i) {
		shared_ptr<Document> documentPtr = make_shared<Document>(i+1);
		updateDocument(contentsPtr->at(i), documentPtr);
		documentPtrs->push_back(documentPtr);
	}

	return documentPtrs;
}

void DocumentBuilder::updateDocument(
		std::pair<std::string, std::vector<std::string>>& content,
		std::shared_ptr<Document> docPtr) {

	const string& title = content.first;
	const vector<string>& body = content.second;

	docPtr->getTitle() = title;

	tokenizerPtr->tokenize(title, docPtr->getTokens());
	for (auto token : docPtr->getTokens()) {
		docPtr->getStemmedContent().push_back(stemmerPtr->stem(token));
	}
	for (size_t i=0; i<body.size(); ++i) {
		tokenizerPtr->tokenize(body[i], docPtr->getTokens());
		for (auto token : docPtr->getTokens()) {
			docPtr->getStemmedContent().push_back(stemmerPtr->stem(token));
		}
	}
}
