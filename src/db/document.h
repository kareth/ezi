#ifndef SRC_DB_DOCUMENT_H_
#define SRC_DB_DOCUMENT_H_

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "io/input_reader_interface.h"
#include "io/stemmer_interface.h"

class Document {
public:
	Document(size_t id, std::shared_ptr<std::vector<std::string>> stemmedContentPtr);
	Document(size_t id);

	std::shared_ptr<std::vector<std::string>>& getStemmedContentPtr()
		{ return stemmedContentPtr; }
	const std::shared_ptr<std::vector<std::string>>& getStemmedContentPtr() const
		{ return stemmedContentPtr; }

	size_t getId() const { return id; }

private:
	size_t id;

	std::shared_ptr<std::vector<std::string>> stemmedContentPtr;
	std::shared_ptr<std::vector<std::string>> contentPtr;
};

class DocumentBuilder {
public:
	DocumentBuilder(std::unique_ptr<InputReaderInterface>,
		std::unique_ptr<StemmerInterface>);

	std::shared_ptr<Document> createOne(std::istream&, size_t id = 0);
	std::shared_ptr<std::vector<std::shared_ptr<Document>>> createMany(std::istream&);

private:
	std::unique_ptr<InputReaderInterface> inputReaderPtr;
	std::unique_ptr<StemmerInterface> stemmerPtr;
};

#endif  // SRC_DB_DOCUMENT_H_
