#include "engine/query_expander.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <wn.h>

#include "db/document_database.h"

using namespace std;

vector<string> QueryExpander::expand(shared_ptr<Document> query, size_t n) {
	if (wninit()) {
		cerr << "Cannot open WordNet database." << endl;
		return vector<string>();
	}

	unordered_map<string, size_t> similaritiesCounter;

	unordered_set<string> uniqueTokens;
	for (const string& str : query->getTokens()) {
		uniqueTokens.insert(str);
	}

	const int searches[] = { SIMPTR, HYPERPTR, HYPOPTR };
	const int parts[] = { ADJ, NOUN, VERB, ADV };
	char *morphword;

	for (string str : uniqueTokens) {
		dflag = fileinfoflag = offsetflag = wnsnsflag = 0;

		char searchword[1024] = {};
		strncpy(searchword, str.c_str(), 1023);

		for (int search : searches) {
			for (int part : parts) {
				updateSimilaritiesCounter(similaritiesCounter, searchword, part, search);

				if ((morphword = morphstr(searchword, part)) != nullptr) {
					do {
						updateSimilaritiesCounter(similaritiesCounter, morphword, part, search);
					} while ((morphword = morphstr(nullptr, part)) != nullptr);
				}
			}
		}
	}

	return createResult(uniqueTokens, similaritiesCounter, n);
}

void QueryExpander::updateSimilaritiesCounter(
		unordered_map<string, size_t>& similaritiesCounter,
		char* searchword, int part, int search) {

	const int whichsense = ALLSENSES;
	SynsetPtr findPtr, synsetPtr, formPtr;

	findPtr = findtheinfo_ds(searchword, part, search, whichsense);
	formPtr = findPtr;

	while (formPtr) {
		synsetPtr = formPtr;
		while (synsetPtr) {
			for (size_t i=0; i<synsetPtr->wcount; ++i) {
				similaritiesCounter[synsetPtr->words[i]]++;
			}

			SynsetPtr listPtr = synsetPtr->ptrlist;
			while (listPtr) {
				for (size_t i=0; i<listPtr->wcount; ++i) {
					similaritiesCounter[listPtr->words[i]]++;
				}
				listPtr = listPtr->nextss;
			}
			synsetPtr = synsetPtr->nextss;
		}
		formPtr = formPtr->nextform;
	}

	free_syns(findPtr);
}

vector<string> QueryExpander::createResult(
		const unordered_set<string>& uniqueTokens,
		const unordered_map<string, size_t>& similaritiesCounter,
		size_t n) {

	vector<pair<string, size_t>> tmpResult;
	tmpResult.reserve(similaritiesCounter.size());
	for (const auto& pr : similaritiesCounter) {
		if (uniqueTokens.find(pr.first) == uniqueTokens.end()) {
			tmpResult.push_back(pr);
		}
	}

	sort(tmpResult.begin(), tmpResult.end(), [](
			const pair<string,size_t>& a, const pair<string,size_t>& b) {
		return a.second > b.second;
	});

	vector<string> result;
	result.reserve(min<size_t>(n, tmpResult.size()));
	for (size_t i=0; i<min<size_t>(n, tmpResult.size()); ++i) {
		string toAdd = tmpResult[i].first;
		replace(toAdd.begin(), toAdd.end(), '_', ' ');
		result.push_back(toAdd);
	}

	return result;
}
