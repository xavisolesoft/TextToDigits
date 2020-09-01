#include "Parser.hpp"

#include <sstream>

Parser::Parser()
{

}

std::vector<Token> Parser::parse(const std::string& text) const
{
	std::vector<Token> res;
	int pos = 0;

	for (std::string word = getNextWord(text, pos); !word.empty(); word = getNextWord(text, pos)) {
		ExtractedToken extractedToken = tryExtractTokenValue(word);

		if (!extractedToken.isExtracted) {
			extractedToken = tryExtractTokenOperation(word);
		}

		if (!extractedToken.isExtracted) {
			extractedToken = tryExtractTokenNop(word);
		}

		extractedToken.token.setText(std::move(word));

		res.emplace_back(std::move(extractedToken.token));
	}

	return res;
}

std::string Parser::getNextWord(const std::string& text, int& pos) const
{
	std::string nextToken;
	int i = pos;

	while (pos < text.size() && isDelimiter(text[pos])) {
		++pos;
	}

	for (; pos < text.size() && !isDelimiter(text[pos]); ++pos) {
		nextToken.push_back(text[pos]);
	}

	return nextToken;
}

bool Parser::isDelimiter(char c)
{
	return c == ' ' || c == '-';
}

Parser::ExtractedToken Parser::tryExtractTokenValue(const std::string& word) const
{
	ExtractedToken res;

	auto valueIter = tokenToValue.find(word);
	if (valueIter != tokenToValue.end()) {
		res.token.setType(Token::Type::VALUE);
		res.token.setValue(valueIter->second);
		res.isExtracted = true;
	}
	else {
		res.isExtracted = false;
	}

	return res;
}

Parser::ExtractedToken Parser::tryExtractTokenOperation(const std::string& word) const
{
	ExtractedToken res;

	auto valueIter = tokenOperator.find(word);
	if (valueIter != tokenOperator.end()) {
		res.token.setType(Token::Type::OPERATOR);
		res.token.setValue(valueIter->second);
		res.isExtracted = true;
	}
	else {
		res.isExtracted = false;
	}

	return res;
}

Parser::ExtractedToken Parser::tryExtractTokenNop(const std::string& word) const
{
	ExtractedToken res;

	res.token.setType(Token::Type::NOP);
	res.token.setValue(-1);
	res.isExtracted = true;

	return res;
}
