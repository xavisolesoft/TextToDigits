#pragma once

#include <string>
#include <cstdint>

class Token
{
public:
	enum class Type
	{
		NOP,
		VALUE,
		OPERATOR
	};

	static constexpr int64_t INVALID_VALUE = -1;

	Token();

	Type getType() const;
	void setType(Type type);

	int64_t getValue() const;
	void setValue(int64_t value);

	const std::string& getText() const;
	void setText(std::string text);

private:
	Type _type = Type::NOP;
	int64_t _value = INVALID_VALUE;
	std::string _text;
};
