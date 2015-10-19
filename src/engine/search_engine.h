#ifndef SRC_ENGINE_SEARCH_ENGINE_H_
#define SRC_ENGINE_SEARCH_ENGINE_H_

#include "db/document_database.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class SearchEngine {
public:
	SearchEngine(std::shared_ptr<DocumentDatabase>);
	std::vector<std::pair<std::shared_ptr<Document>, double>> rank(
		std::shared_ptr<Document> query);

protected:
	virtual double similarity(const std::unordered_map<std::string, double>&,
		double,
		const std::unordered_map<std::string, double>&,
		double);

	double calculateTF(double wordsOccurencies, double maxOccurencies);
	double calculateIDF(double tf, double wordIDF);

private:
	void calculateBagOfWordsMap(std::shared_ptr<Document>,
		std::unordered_map<std::string, double>& tfs);

	double calculateMaxTF(std::shared_ptr<Document>,
		const std::unordered_map<std::string, double>& tfs);

	void updateInvertedFileSet(std::shared_ptr<Document>,
		const std::unordered_map<std::string, double>& tfs);

	void calculateIDFsMap();

	std::shared_ptr<DocumentDatabase> dbPtr;

	std::unordered_map<std::shared_ptr<Document>, std::unordered_map<std::string, double>> bagOfWords;
	std::unordered_map<std::shared_ptr<Document>, double> maxTF;
	std::unordered_map<std::string, std::unordered_set<std::shared_ptr<Document>>> invertedFile;
	std::unordered_map<std::string, double> idfs;
	
};

inline double SearchEngine::calculateTF(double wordOccurencies, double maxOccurencies) {
	return wordOccurencies / maxOccurencies;
}

inline double SearchEngine::calculateIDF(double tf, double wordIDF) {
	return tf * wordIDF;
}

#endif  // SRC_ENGINE_SEARCH_ENGINE_H_
