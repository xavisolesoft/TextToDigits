#pragma once

#include <string>
#include <cstdint>

class Token
{
public:
	enum class Type
	{
		NOT_A_NUMBER, //Normal text without numbers
		VALUE, //one, two, fifteen, fifty...
		HYPHEN_VALUE, //-one, -two,... (needed to differentiate with phone number notation).
		OPERATOR //hundred, thousand
	};

	static constexpr int64_t INVALID_VALUE = -1;
	static const Token NULL_TOKEN;

	Token();

	Type getType() const;
	void setType(Type type);

	int64_t getValue() const;
	void setValue(int64_t value);

	const std::string& getText() const;
	void setText(std::string text);

	char getPreviousSeparator() const;
	void setPreviousSeparator(char separator);

private:
	Type _type = Type::NOT_A_NUMBER;
	int64_t _value = INVALID_VALUE;
	std::string _text;
	char _previousSeparator = '\0';
};
