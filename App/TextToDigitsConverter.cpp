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
		case Token::Type::NOT_A_NUMBER:
			processNotANumberToken(token, context);
			break;
		case Token::Type::VALUE:
			processValueToken(token, context);
			break;
		case Token::Type::HYPHEN_VALUE:
			processHyphenValueToken(token, context);
			break;
		case Token::Type::OPERATOR:
			processOperatorToken(token, context);
		}

		context.previousToken = &token;
	}

	appendPreviousValues(context);

	return context.replacedText;
}

void TextToDigitsConverter::processNotANumberToken(const Token& token, TextToDigitsConverterContext& context)
{
	appendPreviousValues(context);
	appendReplacedTextWithSeparator(context.replacedText, token.getText(), token.getPreviousSeparator());
}

void TextToDigitsConverter::processValueToken(const Token& token, TextToDigitsConverterContext& context)
{
	if (context.previousToken->getType() == Token::Type::VALUE || context.previousToken->getType() == Token::Type::HYPHEN_VALUE) {
		appendPreviousValues(context);
		context.concatenateWithPreviousNumber = true;
	}
	context.previousValues.push_back(token.getValue());
}

void TextToDigitsConverter::processHyphenValueToken(const Token& token, TextToDigitsConverterContext& context)
{
	if (token.getValue() < 10 && token.getValue() > 0
		&& context.previousToken->getType() == Token::Type::VALUE
		&& context.previousToken->getValue() >= 20 && context.previousToken->getValue() <= 90) {
		context.previousValues.back() += token.getValue();
	}
	else {
		processNotANumberToken(token, context);
	}
}

void TextToDigitsConverter::processOperatorToken(const Token& token, TextToDigitsConverterContext& context)
{
	if ((context.previousToken->getType() == Token::Type::VALUE
			|| context.previousToken->getType() == Token::Type::OPERATOR
			|| context.previousToken->getType() == Token::Type::HYPHEN_VALUE)
		&& !context.previousValues.empty()
		&& token.getPreviousSeparator() == ' ') {
			if (token.getValue() > context.previousValues.back()) {
				int64_t sum = 0;
				while (!context.previousValues.empty() && token.getValue() > context.previousValues.back()) {
					sum += context.previousValues.back();
					context.previousValues.pop_back();
				}
				context.previousValues.push_back(sum);
			}
		context.previousValues.back() *= token.getValue();
	}
	else {
		processNotANumberToken(token, context);
	}
}

void TextToDigitsConverter::appendPreviousValues(TextToDigitsConverterContext& context)
{
	if (!context.previousValues.empty()) {
		int64_t totalValue = std::accumulate(context.previousValues.begin(), context.previousValues.end(), (int64_t)0);
		if (context.concatenateWithPreviousNumber) {
			context.replacedText += std::to_string(totalValue);
		}
		else {
			appendReplacedTextWithSeparator(context.replacedText, std::to_string(totalValue), ' ');
		}
		context.previousValues.clear();
		context.concatenateWithPreviousNumber = false;
	}
}

void TextToDigitsConverter::appendReplacedTextWithSeparator(std::string& replacedText, const std::string& textToAppend, char separator)
{
	if (!replacedText.empty()) {
		replacedText += separator;
	}
	replacedText += textToAppend;
}
