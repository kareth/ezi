#ifndef SRC_ENGINE_QUERY_EXPANDER_H_
#define SRC_ENGINE_QUERY_EXPANDER_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "db/document.h"

class QueryExpander {
public:
	std::vector<std::string> expand(std::shared_ptr<Document> query, size_t n = 10);

private:
	void updateSimilaritiesCounter(
		std::unordered_map<std::string, size_t>& similaritiesCounter,
		char* searchword, int part, int search);

	std::vector<std::string> createResult(
		const std::unordered_set<std::string>& uniqueTokens,
		const std::unordered_map<std::string, size_t>& similaritiesCounter,
		size_t n);
};

#endif  // SRC_ENGINE_QUERY_EXPANDER_H_
