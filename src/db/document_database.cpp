#include "db/document_database.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

DocumentDatabaseBuilder::DocumentDatabaseBuilder(
		shared_ptr<DocumentBuilder> documentBuilderPtr)
	: documentBuilderPtr(documentBuilderPtr) {}

shared_ptr<DocumentDatabase> DocumentDatabaseBuilder::create(istream& keywordsStream,
		istream& documentsStream) {
	shared_ptr<DocumentDatabase> dbPtr = make_shared<DocumentDatabase>();

	if (!keywordsStream.good()) {
		cerr << "Bad keywords stream." << endl;
		return nullptr;
	}

	shared_ptr<Document> keywords = documentBuilderPtr->createOne(keywordsStream);
	unordered_set<string> uniqueKeywords(
		keywords->getStemmedContent().begin(),
		keywords->getStemmedContent().end());

	keywords->getStemmedContent() = vector<string>(
		uniqueKeywords.begin(), uniqueKeywords.end());
	
	dbPtr->getKeywords() = keywords;

	if (!documentsStream.good()) {
		cerr << "Bad documents stream." << endl;
		return nullptr;
	}

	dbPtr->getDocuments() = documentBuilderPtr->createMany(documentsStream);

	return dbPtr;
}
