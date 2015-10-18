#include "io/text_file_input_reader.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

shared_ptr<vector<string>>
TextFileInputReader::readKeywords(string filename) {
	shared_ptr<vector<string>> keywordsVectorPtr = make_shared<vector<string>>();

	fstream file;
	file.open(filename, ios::in);
	if (!file.good()) {
		cerr << "Error while openning an input file." << endl;
		return nullptr;
	}

	while (file.good()) {
		string keyword;
		file >> keyword;
		normalize(keyword);
		if (!keyword.empty()) {
			keywordsVectorPtr->push_back(keyword);
		}
	}

	file.close();

	return keywordsVectorPtr;
}

shared_ptr<vector<vector<string>>>
TextFileInputReader::readDocuments(std::string filename) {
	shared_ptr<vector<vector<string>>> documentsVectorPtr
		= make_shared<vector<vector<string>>>();

	fstream file;
	file.open(filename, ios::in);
	if (!file.good()) {
		cerr << "Error while openning an input file." << endl;
		return nullptr;
	}

	vector<string> document;
	while (file.good()) {
		string line;
		getline(file, line);
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
			documentsVectorPtr->push_back(document);
			document.clear();
		}
	}

	return documentsVectorPtr;
}

string& TextFileInputReader::trim(string& str) {
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

vector<string> TextFileInputReader::split(const string& str, int delimiter(int)) {
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

string& TextFileInputReader::normalize(string& str) {
	trim(str);

	transform(str.begin(), str.end(), str.begin(), ::tolower);

	str.erase(remove_if(str.begin(), str.end(), [](char ch) {
		return !isalpha(ch);
	}), str.end());

	return str;
}
