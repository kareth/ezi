#ifndef SRC_DB_DOCUMENT_H_
#define SRC_DB_DOCUMENT_H_

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "io/input_reader_interface.h"
#include "io/tokenizer_base.h"
#include "io/stemmer_interface.h"

class Document {
public:
	Document(size_t id);

	std::string& getTitle() { return title; }
	const std::string& getTitle() const { return title; }

	std::vector<std::string>& getTokens() { return tokens; }
	const std::vector<std::string>& getTokens() const { return tokens; }

	std::vector<std::string>& getStemmedContent()
		{ return stemmedContent; }
	const std::vector<std::string>& getStemmedContent() const
		{ return stemmedContent; }

	size_t getId() const { return id; }

private:
	size_t id;

	std::string title;
	std::vector<std::string> tokens;
	std::vector<std::string> stemmedContent;
};

class DocumentBuilder {
public:
	DocumentBuilder(std::unique_ptr<InputReaderInterface>,
		std::unique_ptr<TokenizerBase>,
		std::unique_ptr<StemmerInterface>);

	std::shared_ptr<Document> createOne(std::istream&, size_t id = 0);
	std::shared_ptr<std::vector<std::shared_ptr<Document>>> createMany(std::istream&);

private:
	void updateDocument(std::pair<std::string, std::vector<std::string>>&,
		std::shared_ptr<Document>);

	std::unique_ptr<InputReaderInterface> inputReaderPtr;
	std::unique_ptr<TokenizerBase> tokenizerPtr;
	std::unique_ptr<StemmerInterface> stemmerPtr;
};

#endif  // SRC_DB_DOCUMENT_H_
