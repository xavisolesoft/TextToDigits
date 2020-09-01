#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Parser.hpp"

class TextToDigitsConverterContext;

class TextToDigitsConverter
{
public:
	TextToDigitsConverter();

	std::string replaceTextForDigits(const std::string& text) const;

private:
	static void processNotANumberToken(const Token& token, TextToDigitsConverterContext& context);
	static void processValueToken(const Token& token, TextToDigitsConverterContext& context);
	static void processHyphenValueToken(const Token& token, TextToDigitsConverterContext& context);
	static void processOperatorToken(const Token& token, TextToDigitsConverterContext& context);

	static void appendPreviousValues(TextToDigitsConverterContext& context);
	static void appendReplacedTextWithSeparator(std::string& replacedText, const std::string& textToAppend);

private:
	Parser parser;
};
