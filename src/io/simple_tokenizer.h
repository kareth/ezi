#ifndef SRC_IO_SIMPLE_TOKENIZER_H_
#define SRC_IO_SIMPLE_TOKENIZER_H_

#include "io/tokenizer_base.h"

#include <memory>
#include <string>
#include <vector>

class SimpleTokenizer : public TokenizerBase {
private:
	virtual std::vector<std::string>& split(
		const std::string&,	std::vector<std::string>& result,
		int delimiter(int) = ::isspace);

	virtual std::string& normalize(std::string&);
};

#endif  // SRC_IO_SIMPLE_TOKENIZER_H_
