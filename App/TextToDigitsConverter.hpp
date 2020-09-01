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
	static void appendPreviousValues(TextToDigitsConverterContext& context);
	static void appendReplacedTextWithSeparator(std::string& replacedText, const std::string& textToAppend);

private:
	Parser parser;
};
