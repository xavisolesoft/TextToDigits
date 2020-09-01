#include <iostream>
#include <string>

#include "TextToDigitsConverter.hpp"

int main()
{
	TextToDigitsConverter textToDigitsConverter;

	for (std::string line; std::getline(std::cin, line); ) {
		std::cout << textToDigitsConverter.replaceTextForDigits(line) << std::endl;
	}
	
	return 0;
}
