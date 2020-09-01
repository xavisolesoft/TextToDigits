#pragma once

class TextToDigitsConverterContext
{
public:
	std::string replacedText;
	std::vector<int64_t> previousValues;
	Token::Type previousTokenType = Token::Type::NOP;
	bool concatenateWithPreviousNumber = false;
};
