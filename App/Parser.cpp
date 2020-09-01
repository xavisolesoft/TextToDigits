#include "Parser.hpp"

#include <sstream>
#include <cctype>


Parser::Parser()
{

}

std::vector<Token> Parser::parse(const std::string& text) const
{
	std::vector<Token> res;
	int pos = 0;

	for (NextWord nextWord = getNextWord(text, pos); !nextWord.word.empty(); nextWord = getNextWord(text, pos)) {
		std::string cleanWord = toCleanWord(nextWord.word);
		ExtractedToken extractedToken = tryExtractTokenValue(cleanWord, nextWord.previousSeparator);

		if (!extractedToken.isExtracted) {
			extractedToken = tryExtractTokenOperation(cleanWord);
		}

		if (!extractedToken.isExtracted) {
			extractedToken = tryExtractTokenNop(cleanWord);
		}

		extractedToken.token.setText(std::move(nextWord.word));
		extractedToken.token.setPreviousSeparator(nextWord.previousSeparator);

		res.emplace_back(std::move(extractedToken.token));
	}

	return res;
}

Parser::NextWord Parser::getNextWord(const std::string& text, int& pos) const
{
	NextWord nextWord;

	while (pos < text.size() && isSeparator(text[pos])) {
		++pos;
	}

	nextWord.previousSeparator = ' ';
	if (pos > 0) {
		nextWord.previousSeparator = text[pos-1];
	}

	for (; pos < text.size() && !isSeparator(text[pos]); ++pos) {
		nextWord.word.push_back(text[pos]);
	}

	return nextWord;
}

bool Parser::isSeparator(char c)
{
	return c == ' ' || c == '-';
}

Parser::ExtractedToken Parser::tryExtractTokenValue(const std::string& word, char previousSeparator) const
{
	ExtractedToken res;

	auto valueIter = tokenToValue.find(word);
	if (valueIter != tokenToValue.end()) {
		if (previousSeparator == '-') {
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

std::string Parser::toCleanWord(const std::string& word)
{
	if (word.empty()) {
		return word;
	}
	else {
		std::string cleanedWord = word;
		cleanedWord[0] = static_cast<char>(std::tolower(word[0]));
		return cleanedWord;
	}
}
