#ifndef STEMMER_INTERFACE_H_
#define STEMMER_INTERFACE_H_

#include <string>

class StemmerInterface {
public:
	virtual std::string stem(const std::string&) = 0;
};

#endif  // STEMMER_INTERFACE_H_
