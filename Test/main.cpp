#include <iostream>
#include <string>
#include <fstream>

#include "TextToDigitsConverter.hpp"

struct TestInfo
{
	std::string input;
	std::string output;
};

int main()
{
	std::vector<TestInfo> testDataSet =
	{
		{"five", "5"},
		{"six", "6"},
		{"seven", "7"},
		{"eight", "8"},
		{"nine", "9"},
		{"ten", "10"},
		{"eleven", "11"},
		{"twelve", "12"},
		{"thirteen", "13"},
		{"fourteen", "14"},
		{"fifteen", "15"},
		{"sixteen", "16"},
		{"seventeen", "17"},
		{"eighteen", "18"},
		{"nineteen", "19"},
		{"twenty", "20"},
		{"twenty-one", "21"},
		{"twenty-two", "22"},
		{"twenty-three", "23"},
		{"twenty-four", "24"},
		{"twenty-five", "25"},
		{"twenty-six", "26"},
		{"twenty-seven", "27"},
		{"twenty-eight", "28"},
		{"twenty-nine", "29"},
		{"thirty", "30"},
		{"thirty-one", "31"},
		{"forty", "40"},
		{"fifty", "50"},
		{"sixty", "60"},
		{"seventy", "70"},
		{"eighty", "80"},
		{"ninety", "90"},
		{"one hundred", "100"},
		{"five hundred", "500"},
		{"one thousand", "1000"},
		{"one thousand five hundred", "1500"},
		{"fifteen hundred", "1500"},
		{"one hundred thousand", "100000"},
		{"one million", "1000000"},
		{"one billion", "1000000000"},
		{"Good morning!", "Good morning!"},
		{"One hundred and three", "103"},
		{"two thousand, one hundred", "2100"},
		{"two thousand one hundred", "2100"},
		{"I have two brothers. There are thirty-one days in January.", "I have 2 brothers. There are 31 days in January."},
		{"I am thirty-three years old. My sister is twenty-seven years old.", "I am 33 years old. My sister is 27 years old."},
		{"She was born in nineteen seventy-five (1975).", "She was born in 1975 (1975)."},
		{"twenty-nineteen", "20-nineteen"},
		{"hundred", "hundred"},
		{"hundred thousand", "hundred thousand"},
		{"ten-one", "10-one"},
		{"twenty-ten", "20-ten"},
		{"sixty-zero", "60-zero"},
		{"hundred-two", "hundred-two"},
		{"two-hundred", "2-hundred"},
		{"two three forty", "2340"},
		{"twenty-seven O thirty-one", "27031"},
		{"one hundred ninety-eight million seven hundred sixty-eight thousand nine hundred nine", "198768909"},
		{"nine hundred thirty-four billion seven hundred ninety-eight million three hundred forty-three thousand seventy", "934798343070"},
		{"nine hundred thirty-four billion seven good morning hundred ninety-eight million three hundred forty-three thousand seventy", "934000000007 good morning hundred 98343070"},
		{"nine hundred thirty-four billion seven O hundred ninety-eight million three hundred forty-three thousand seventy", "93400000000798343070"},
		{"three hundred forty-seven billion two hundred ninety-seven million two hundred ninety-four thousand seven hundred thirty-nine", "347297294739"},
		{"A hundred", "100"},
		{"a thousand", "1000"},
		{"a million", "1000000"},
		{"a billion", "1000000000"},
		{"a three", "a 3"},
		{"twenty-a", "20-a"}
	};

	TextToDigitsConverter textToDigitsConverter;
	for (const TestInfo& testInfo: testDataSet) {
		std::string textToDigits = textToDigitsConverter.replaceTextForDigits(testInfo.input);
		if (testInfo.output != textToDigits) {
			std::cout << "\u001b[31mERROR:\u001b[0m " << "\"" << testInfo.input << "\"" << " is " << "\"" << textToDigits
				<< "\"" << " but should be " << "\"" << testInfo.output << "\"" << "." << std::endl;
		}
		std::cout << testInfo.input << "     " << testInfo.output << std::endl;
	}
	
	return 0;
}
