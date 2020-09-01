#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>

#include "Token.hpp"

class Parser
{
public:
	Parser();

	std::vector<Token> parse(const std::string& text) const;

private:
	struct NextWord
	{
		char previousDelimiter = ' ';
		std::string word;

	};
	NextWord getNextWord(const std::string& text, int& pos) const;
	static bool isDelimiter(char c);

	struct ExtractedToken
	{
		bool isExtracted = false;
		Token token;
	};
	ExtractedToken tryExtractTokenValue(const std::string& word, char previousDelimiter) const;
	ExtractedToken tryExtractTokenOperation(const std::string& word) const;
	ExtractedToken tryExtractTokenNop(const std::string& word) const;

	static std::string toCleanWord(const std::string& word);

	const std::unordered_map<std::string, int64_t> tokenToValue =
	{
		{"o", 0},
		{"zero", 0},
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9},
		{"ten", 10},
		{"eleven", 11},
		{"twelve", 12},
		{"thirteen", 13},
		{"fourteen", 14},
		{"fifteen", 15},
		{"sixteen", 16},
		{"seventeen", 17},
		{"eighteen", 18},
		{"nineteen", 19},
		{"twenty", 20},
		{"thirty", 30},
		{"forty", 40},
		{"fifty", 50},
		{"sixty", 60},
		{"seventy", 70},
		{"eighty", 80},
		{"ninety", 90}
	};

	const std::unordered_map<std::string, int64_t> tokenOperator =
	{
		{"hundred", 100},
		{"thousand", 1000},
		{"million", 1000000},
		{"billion", 1000000000}
	};
};
