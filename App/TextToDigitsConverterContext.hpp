#pragma once

class TextToDigitsConverterContext
{
public:
	std::string replacedText;
	std::vector<int64_t> previousValues;
	Token::Type previousTokenType = Token::Type::NOT_A_NUMBER;
	bool concatenateWithPreviousNumber = false;
};
