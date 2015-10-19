#include "engine/search_engine.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "db/document_database.h"

using namespace std;

SearchEngine::SearchEngine(shared_ptr<DocumentDatabase> dbPtr)
		: dbPtr(dbPtr) {

	for (shared_ptr<Document> docPtr : *dbPtr->getDocuments()) {
		calculateBagOfWordsMap(docPtr, bagOfWords[docPtr]);
		maxTF[docPtr] = calculateMaxTF(docPtr, bagOfWords[docPtr]);
		updateInvertedFileSet(docPtr, bagOfWords[docPtr]);
	}

	calculateIDFsMap();
}

vector<pair<shared_ptr<Document>, double>>
SearchEngine::rank(shared_ptr<Document> query) {

	unordered_map<string, double> queryBagOfWords;
	calculateBagOfWordsMap(query, queryBagOfWords);

	unordered_set<shared_ptr<Document>> candidates;
	for (auto pr : queryBagOfWords) {
		if (pr.second > 0) {
			unordered_set<shared_ptr<Document>> docs = invertedFile[pr.first];
			candidates.insert(docs.begin(), docs.end());
		}
	}

	vector<pair<shared_ptr<Document>, double>> result;
	result.reserve(candidates.size());

	for (shared_ptr<Document> docPtr : candidates) {
		result.emplace_back(
			make_pair(
				docPtr,
				similarity(queryBagOfWords,
					calculateMaxTF(query, queryBagOfWords),
					bagOfWords[docPtr],
					maxTF[docPtr])
			));
	}

	sort(result.begin(), result.end(),
		[](const pair<shared_ptr<Document>, double>& a,
				const pair<shared_ptr<Document>, double>& b) -> bool {
			return a.second > b.second;
		});

	return result;
}

double SearchEngine::similarity(
		const unordered_map<string, double>& aDocBagOfWords,
		double aMaxOccurencies,
		const unordered_map<string, double>& bDocBagOfWords,
		double bMaxOccurencies) {

	double counter = 0.0;
	double denominatorA = 0.0;
	double denominatorB = 0.0;

	for (auto keyword : dbPtr->getKeywords()->getStemmedContent()) {
		const double idf = idfs[keyword];
		const double aTF = calculateTF(aDocBagOfWords.at(keyword), aMaxOccurencies);
		const double bTF = calculateTF(bDocBagOfWords.at(keyword), bMaxOccurencies);
		const double aIDF = calculateIDF(aTF, idf);
		const double bIDF = calculateIDF(bTF, idf);

		counter += aIDF*bIDF;
		denominatorA += aIDF*aIDF;
		denominatorB += bIDF*bIDF;
	}

	double denominator = sqrt(denominatorA*denominatorB);

	return denominator == 0.0 ? 0.0 : counter / denominator;
}

void SearchEngine::calculateBagOfWordsMap(shared_ptr<Document> documentPtr,
		unordered_map<string, double>& bow) {

	bow.clear();

	for (string str : dbPtr->getKeywords()->getStemmedContent()) {
		bow[str] = 0;
	}

	for (string word : documentPtr->getStemmedContent()) {
		auto it = bow.find(word);
		if (it != bow.end()) {
			it->second++;
		}
	}
}

double SearchEngine::calculateMaxTF(std::shared_ptr<Document> documentPtr,
		const unordered_map<string, double>& bagOfWords) {
	double maxOccurencies = 0.0;

	for (auto pr : bagOfWords) {
		maxOccurencies = max(maxOccurencies, pr.second);
	}

	return maxOccurencies;
}

void SearchEngine::updateInvertedFileSet(shared_ptr<Document> documentPtr,
		const unordered_map<string, double>& bagOfWords) {

	for (auto pr : bagOfWords) {
		if (pr.second > 0) invertedFile[pr.first].insert(documentPtr);
	}
}

void SearchEngine::calculateIDFsMap() {
	// cout << "idfs:" << endl;
	double dbSize = dbPtr->getDocuments()->size();
	for (auto pr : invertedFile) {
		string term = pr.first;
		double occurencies = pr.second.size();
		idfs[term] = log(dbSize / occurencies);

		// cout << term << ": " << idfs[term] << endl;
	}
}
