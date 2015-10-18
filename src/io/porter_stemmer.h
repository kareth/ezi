#ifndef PORTER_STEMMER_H_
#define PORTER_STEMMER_H_

#include "io/stemmer_interface.h"

#include <string>

class PorterStemmer : public StemmerInterface {
public:
	virtual std::string stem(const std::string&);

private:
	static const size_t BUFFER_SIZE;
};

#endif  // PORTER_STEMMER_H_
