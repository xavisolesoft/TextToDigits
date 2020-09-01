#include "TextToDigitsConverter.hpp"

#include "Token.hpp"

TextToDigitsConverter::TextToDigitsConverter()
{

}

std::string TextToDigitsConverter::replaceTextForDigits(const std::string& text) const
{
	std::string replacedText;
	int64_t previousValue = Token::INVALID_VALUE;

	for (const Token& token : parser.parse(text)) {
		switch (token.getType())
		{
		case Token::Type::NOP:
			if (previousValue != Token::INVALID_VALUE) {
				appendReplacedText(replacedText, std::to_string(previousValue));
			}
			appendReplacedText(replacedText, token.getText());
			break;
		case Token::Type::VALUE:
			if (previousValue == Token::INVALID_VALUE) {
				previousValue = token.getValue();
			}
			else {
				previousValue += token.getValue();
			}
			break;
		case Token::Type::OPERATOR:
			//TODO
			;
		}
	}

	if (previousValue != Token::INVALID_VALUE) {
		appendReplacedText(replacedText, std::to_string(previousValue));
	}

	return replacedText;
}

void TextToDigitsConverter::appendReplacedText(std::string& replacedText, const std::string& textToAppend)
{
	if (!replacedText.empty()) {
		replacedText += " ";
	}
	replacedText += textToAppend;
}
