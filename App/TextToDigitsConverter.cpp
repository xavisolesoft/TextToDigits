#include "TextToDigitsConverter.hpp"

#include <numeric>

#include "Token.hpp"

TextToDigitsConverter::TextToDigitsConverter()
{

}

std::string TextToDigitsConverter::replaceTextForDigits(const std::string& text) const
{
	std::string replacedText;
	std::vector<int64_t> previousValues;

	for (const Token& token : parser.parse(text)) {
		switch (token.getType())
		{
		case Token::Type::NOP:
			if (!previousValues.empty()) {
				int64_t totalValue = std::accumulate(previousValues.begin(), previousValues.end(), 0);
				appendReplacedText(replacedText, std::to_string(totalValue));
			}
			appendReplacedText(replacedText, token.getText());
			break;
		case Token::Type::VALUE:
			previousValues.push_back(token.getValue());
			break;
		case Token::Type::OPERATOR:
			previousValues.back() *= token.getValue();
		}
	}

	if (!previousValues.empty()) {
		int64_t totalValue = std::accumulate(previousValues.begin(), previousValues.end(), 0);
		appendReplacedText(replacedText, std::to_string(totalValue));
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
