#include "io/text_input_reader.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

shared_ptr<vector<pair<string, vector<string>>>> TextInputReader::read(
		istream& is) {

	shared_ptr<vector<pair<string, vector<string>>>> contents
		= make_shared<vector<pair<string, vector<string>>>>();

	string title;
	vector<string> body;
	while (is.good()) {
		string line;
		getline(is, line);
		trim(line);
		if (!line.empty()) {
			if (title.empty()) {
				title = line;
			} else {
				body.push_back(line);
			}
		} else if (!title.empty()) {
			contents->emplace_back(make_pair(title, body));
			title.clear();
			body.clear();
		}
	}

	if (!title.empty()) {
		contents->emplace_back(make_pair(title, body));
	}

	return contents;
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
