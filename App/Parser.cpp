#include "Parser.hpp"

#include <sstream>

Parser::Parser()
{

}

std::vector<Token> Parser::parse(const std::string& text) const
{
	std::vector<Token> res;
	int pos = 0;

	for (NextWord nextWord = getNextWord(text, pos); !nextWord.word.empty(); nextWord = getNextWord(text, pos)) {
		ExtractedToken extractedToken = tryExtractTokenValue(nextWord.word, nextWord.previousDelimiter);

		if (!extractedToken.isExtracted) {
			extractedToken = tryExtractTokenOperation(nextWord.word);
		}

		if (!extractedToken.isExtracted) {
			extractedToken = tryExtractTokenNop(nextWord.word);
		}

		extractedToken.token.setText(std::move(nextWord.word));

		res.emplace_back(std::move(extractedToken.token));
	}

	return res;
}

Parser::NextWord Parser::getNextWord(const std::string& text, int& pos) const
{
	NextWord nextWord;

	while (pos < text.size() && isDelimiter(text[pos])) {
		++pos;
	}

	nextWord.previousDelimiter = ' ';
	if (pos > 0) {
		nextWord.previousDelimiter = text[pos-1];
	}

	for (; pos < text.size() && !isDelimiter(text[pos]); ++pos) {
		nextWord.word.push_back(text[pos]);
	}

	return nextWord;
}

bool Parser::isDelimiter(char c)
{
	return c == ' ' || c == '-';
}

Parser::ExtractedToken Parser::tryExtractTokenValue(const std::string& word, char previousDelimiter) const
{
	ExtractedToken res;

	auto valueIter = tokenToValue.find(word);
	if (valueIter != tokenToValue.end()) {
		if (previousDelimiter == '-') {
			res.token.setType(Token::Type::HYPHEN_VALUE);
		}
		else {
			res.token.setType(Token::Type::VALUE);
		}
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

	res.token.setType(Token::Type::NOT_A_NUMBER);
	res.token.setValue(-1);
	res.isExtracted = true;

	return res;
}
