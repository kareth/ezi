#include "io/simple_tokenizer.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

vector<string>& SimpleTokenizer::split(
		const string& str, vector<string>& result, int delimiter(int)) {
	auto e = str.end();
	auto i = str.begin();
	while (i != e){
		i = find_if_not(i, e, delimiter);
		if (i == e) break;
		auto j = find_if(i, e, delimiter);
		result.push_back(string(i,j));
		i = j;
	}
	return result;
}

string& SimpleTokenizer::normalize(string& str) {
	// trim(str);

	transform(str.begin(), str.end(), str.begin(), ::tolower);

	str.erase(remove_if(str.begin(), str.end(), [](char ch) {
		return !isalpha(ch);
	}), str.end());

	return str;
}
