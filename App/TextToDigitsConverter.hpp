#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Parser.hpp"


class TextToDigitsConverter
{
public:
	TextToDigitsConverter();

	std::string replaceTextForDigits(const std::string& text) const;

private:
	static void appendReplacedText(std::string& replacedText, const std::string& textToAppend);

private:
	Parser parser;
};
