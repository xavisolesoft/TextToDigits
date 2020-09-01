#include <iostream>
#include <string>
#include <fstream>

#include "TextToDigitsConverter.hpp"

int main()
{
	std::ifstream dataSetStream("TestDataSet.txt");
	if (!dataSetStream.is_open()) {
		std::cout << "Cannot open TestDataSet.txt" << std::endl;
		exit(0);
	}

	TextToDigitsConverter textToDigitsConverter;
	for (std::string outputLine, inputLine; std::getline(dataSetStream, outputLine, '\t') && std::getline(dataSetStream, inputLine, '\n'); ) {
		std::string textToDigits = textToDigitsConverter.replaceTextForDigits(inputLine);
		if (outputLine != textToDigits) {
			std::cout << "\u001b[31mERROR:\u001b[0m " << "\"" << inputLine << "\"" << " is " << textToDigits << " but should be " << outputLine << "." << std::endl;
		}
		std::cout << inputLine << "     " << outputLine << std::endl;
	}
	
	return 0;
}
