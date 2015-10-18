#include "io/porter_stemmer.h"

#include <cstring>
#include <string>

extern "C" {
#include "io/porter_stemmer_impl.h"
}

using namespace std;

const size_t PorterStemmer::BUFFER_SIZE = 1024;

string PorterStemmer::stem(const string& str) {
	char buf[BUFFER_SIZE];
	strncpy(buf, str.c_str(), sizeof(buf));
	buf[sizeof(buf)-1] = 0;
	buf[::stem(buf, 0, strlen(buf)-1)+1] = 0;

	return string(buf);
}
