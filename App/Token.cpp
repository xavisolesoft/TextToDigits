#include "Token.hpp"

const Token Token::NULL_TOKEN;

Token::Token()
{

}

Token::Type Token::getType() const
{
	return _type;
}

void Token::setType(Type type)
{
	_type = type;
}

int64_t Token::getValue() const
{
	return _value;
}

void Token::setValue(int64_t value)
{
	_value = value;
}

const std::string& Token::getText() const
{
	return _text;
}

void Token::setText(std::string text)
{
	_text = std::move(text);
}

char Token::getPreviousSeparator() const
{
	return _previousSeparator;
}

void Token::setPreviousSeparator(char separator)
{
	_previousSeparator = separator;
}
