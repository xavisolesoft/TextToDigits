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
	appendReplacedTextWithSeparator(context.replacedText, token.getText());
}

void TextToDigitsConverter::processValueToken(const Token& token, TextToDigitsConverterContext& context)
{
	if (context.previousToken->getType() == Token::Type::VALUE) {
		appendPreviousValues(context);
		context.concatenateWithPreviousNumber = true;
	}
	context.previousValues.push_back(token.getValue());
}

void TextToDigitsConverter::processHyphenValueToken(const Token& token, TextToDigitsConverterContext& context)
{
	if (token.getValue() < 10 && token.getValue() > 0 && context.previousToken->getType() == Token::Type::VALUE) {
		context.previousValues.push_back(token.getValue());
	}
	else {
		processNotANumberToken(token, context);
	}
}

void TextToDigitsConverter::processOperatorToken(const Token& token, TextToDigitsConverterContext& context)
{
	if ((context.previousToken->getType() == Token::Type::VALUE || context.previousToken->getType() == Token::Type::OPERATOR)
		&& !context.previousValues.empty()) {
		context.previousValues.back() *= token.getValue();
	}
	else {
		processNotANumberToken(token, context);
	}
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
