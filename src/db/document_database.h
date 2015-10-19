#ifndef SRC_DB_DOCUMENT_DATABASE_H_
#define SRC_DB_DOCUMENT_DATABASE_H_

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "db/document.h"

class DocumentDatabase {
public:
	std::shared_ptr<Document>&
		getKeywords() { return keywords; }
	const std::shared_ptr<Document>&
		getKeywords() const { return keywords; }

	std::shared_ptr<std::vector<std::shared_ptr<Document>>>&
		getDocuments() { return documents; }
	const std::shared_ptr<std::vector<std::shared_ptr<Document>>>&
		getDocuments() const { return documents; }

private:
	std::shared_ptr<Document> keywords;
	std::shared_ptr<std::vector<std::shared_ptr<Document>>> documents;
};

#include "io/input_reader_interface.h"
#include "io/stemmer_interface.h"

class DocumentDatabaseBuilder {
public:
	DocumentDatabaseBuilder(std::shared_ptr<DocumentBuilder>);
	
	std::shared_ptr<DocumentDatabase> create(std::istream& keywordsStream,
		std::istream& documentsStream);

private:
	std::shared_ptr<DocumentBuilder> documentBuilderPtr;
};

#endif  // SRC_DB_DOCUMENT_DATABASE_H_
