#pragma once

#include "Token.hpp"

class TextToDigitsConverterContext
{
public:
	TextToDigitsConverterContext()
	{

	}

	std::string replacedText;
	std::vector<int64_t> previousValues;
	const Token* previousToken = &Token::NULL_TOKEN;
	bool concatenateWithPreviousNumber = false;
};
