#include "io/text_input_reader.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

shared_ptr<vector<shared_ptr<vector<string>>>>
TextInputReader::read(std::istream& is) {
	shared_ptr<vector<shared_ptr<vector<string>>>> docsPtr
		= make_shared<vector<shared_ptr<vector<string>>>>();

	vector<string> document;
	while (is.good()) {
		string line;
		getline(is, line);
		trim(line);
		if (!line.empty()) {
			vector<string> vs = split(line);
			for (string& el : vs) {
				normalize(el);
			}
			vs.erase(remove_if(vs.begin(), vs.end(), [](const string& str) {
				return str.empty();
			}), vs.end());
			document.insert(document.end(), vs.begin(), vs.end());
			// for (string el : vs) cout << "'" << el << "'" " "; cout << endl;
		} else if (!document.empty()) {
			docsPtr->push_back(make_shared<vector<string>>(document));
			document.clear();
		}
	}

	if (!document.empty()) {
		docsPtr->push_back(make_shared<vector<string>>(document));
	}

	return docsPtr;
}

string& TextInputReader::trim(string& str) {
	auto it1 = find_if(str.rbegin(), str.rend(), [](char ch) {
		return !isspace<char>(ch, locale::classic());
	} );
	str.erase(it1.base(), str.end());

	auto it2 = find_if(str.begin(), str.end(), [](char ch) {
		return !std::isspace<char>(ch , locale::classic());
	 } );
	str.erase(str.begin(), it2);

	return str;
}

vector<string> TextInputReader::split(const string& str, int delimiter(int)) {
	vector<string> result;
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

string& TextInputReader::normalize(string& str) {
	trim(str);

	transform(str.begin(), str.end(), str.begin(), ::tolower);

	str.erase(remove_if(str.begin(), str.end(), [](char ch) {
		return !isalpha(ch);
	}), str.end());

	return str;
}
