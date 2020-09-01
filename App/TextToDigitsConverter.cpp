#include "TextToDigitsConverter.hpp"

TextToDigitsConverter::TextToDigitsConverter()
{

}

int64_t TextToDigitsConverter::convert(const std::string& text) const
{
	int64_t digits = -1;

	auto valueIter = tokenToValue.find(text);
	if (valueIter != tokenToValue.end()) {
		return valueIter->second;
	}

	return digits;
}
