#include "io/tokenizer_base.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string>& TokenizerBase::tokenize(
		const std::string& line, vector<string>& result) {

	result.clear();

	split(line, result);

	for (string& el : result) {
		normalize(el);
	}

	result.erase(remove_if(result.begin(), result.end(), [](const string& str) {
		return str.empty();
	}), result.end());

	return result;
}

