#ifndef SRC_IO_TOKENIZER_BASE_H_
#define SRC_IO_TOKENIZER_BASE_H_

#include <string>
#include <vector>

class TokenizerBase {
public:
	virtual std::vector<std::string>& tokenize(
		const std::string&, std::vector<std::string>&);

protected:
	virtual std::vector<std::string>& split(
		const std::string&,	std::vector<std::string>& result,
		int delimiter(int) = ::isspace) = 0;

	virtual std::string& normalize(std::string&) = 0;
};

#endif  // SRC_IO_TOKENIZER_BASE_H_
