#include "TextToDigitsConverter.hpp"

#include <numeric>

#include "Token.hpp"
#include "TextToDigitsConverterContext.hpp"

TextToDigitsConverter::TextToDigitsConverter()
{

}

std::string TextToDigitsConverter::replaceTextForDigits(const std::string& text) const
{
	TextToDigitsConverterContext context;

	for (const Token& token : parser.parse(text)) {
		switch (token.getType())
		{
		case Token::Type::NOP:
			appendPreviousValues(context);
			appendReplacedTextWithSeparator(context.replacedText, token.getText());
			break;
		case Token::Type::VALUE:
			if (context.previousTokenType == Token::Type::VALUE) {
				appendPreviousValues(context);
				context.concatenateWithPreviousNumber = true;
			}
			context.previousValues.push_back(token.getValue());
			break;
		case Token::Type::HYPHEN_VALUE:
			context.previousValues.push_back(token.getValue());
			break;
		case Token::Type::OPERATOR:
			context.previousValues.back() *= token.getValue();
		}

		context.previousTokenType = token.getType();
	}

	appendPreviousValues(context);

	return context.replacedText;
}

void TextToDigitsConverter::appendPreviousValues(TextToDigitsConverterContext& context)
{
	if (!context.previousValues.empty()) {
		int64_t totalValue = std::accumulate(context.previousValues.begin(), context.previousValues.end(), 0);
		if (context.concatenateWithPreviousNumber) {
			context.replacedText += std::to_string(totalValue);
		}
		else {
			appendReplacedTextWithSeparator(context.replacedText, std::to_string(totalValue));
		}
		context.previousValues.clear();
		context.concatenateWithPreviousNumber = false;
	}
}

void TextToDigitsConverter::appendReplacedTextWithSeparator(std::string& replacedText, const std::string& textToAppend)
{
	if (!replacedText.empty()) {
		replacedText += " ";
	}
	replacedText += textToAppend;
}
