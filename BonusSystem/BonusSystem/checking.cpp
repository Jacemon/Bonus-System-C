#include <iostream>
#include <sstream>
#include <regex>

#include "checking.h"

const char errorStringColor[] = "\033[31m";
const char outputStringColor[] = "\033[0m";
const char correctStringColor[] = "\033[32m";
const char saveCursorPosition[] = "\033[s";
const char restoreCursorPosition[] = "\033[u";

#define ERRC errorStringColor
#define OUTC outputStringColor
#define CORC correctStringColor
#define SAVE saveCursorPosition
#define REST restoreCursorPosition

bool check::isInt32Value(std::string value) {
	return std::regex_match(value, std::regex(R"(^[+-]?\d+$)"));
}
bool check::isNaturalValue(std::string value) {
	return std::regex_match(value, std::regex(R"(^0*[1-9]\d*$)"));
}
bool check::isDoubleValue(std::string value) {
	return std::regex_match(value, std::regex(R"(^[-+]?\d*\.?\d*(?:[eE][-+]?\d+)?$)"));
}
bool check::isWordValue(std::string value) {
	return std::regex_match(value, std::regex(R"(^[a-zA-Zà-ÿÀ-ß¸¨]+$)"));
}
bool check::isUppercaseWordValue(std::string value) {
	return std::regex_match(value, std::regex(R"(^[A-ZÀ-ß¨]+$)"));
}
bool check::isLovercaseWordValue(std::string value) {
	return std::regex_match(value, std::regex(R"(^[a-zà-ÿ¸]+$)"));
}
bool check::isProperNameValue(std::string value) {
	return std::regex_match(value, std::regex(R"(^[A-ZÀ-ß¨][a-zà-ÿ¸]*$)"));
}
bool check::isLetterValue(char value) {
	std::ostringstream os;
	os << value;
	return std::regex_match(os.str(), std::regex(R"(^[a-zA-Zà-ÿÀ-ß¸¨]$)"));
}
bool check::isLetterValue(std::string value) {
	return std::regex_match(value, std::regex(R"(^[a-zA-Zà-ÿÀ-ß¸¨]$)"));
}
bool check::isPasswordValue(std::string value, int symbolCount, int uppercaseLetterCount, 
	int lowercaseLetterCount, int numberCount, int specialCharacterCount, int symbolsRepeats) {

	std::string flags = "1111";

	if (uppercaseLetterCount < 0) {
		flags[0] = '0';
	}
	if (lowercaseLetterCount < 0) {
		flags[1] = '0';
	}
	if (numberCount < 0) {
		flags[2] = '0';
	}
	if (specialCharacterCount < 0) {
		flags[3] = '0';
	}

	std::string endOfField = ",})";
	std::string allSymbols[] = {
		"(?=(?:.*[A-Z]){" + std::to_string(uppercaseLetterCount) + endOfField, // uppercase
		"(?=(?:.*[a-z]){" + std::to_string(lowercaseLetterCount) + endOfField, // lowercase
		R"((?=(?:.*\d){)" + std::to_string(numberCount) + endOfField, // numbers
		R"((?=(?:.*[!@#$%^&*()\\\-_=+{};:,<.>\[\]~ '`\/?|"]){)" + std::to_string(specialCharacterCount) + endOfField // special
	};
	std::string allSymbolsEnd[] = {
		"A-Z", 
		"a-z", 
		"0-9", 
		R"(!@#$%^&*()\\\-_=+{};:,<.>\[\]~ '`\/?|")"
	};

	std::string result = "^";
	std::string resultEnd = "([";
	for (int i = 0; i < 4; i++) {
		if (flags[i] == '1') {
			resultEnd += allSymbolsEnd[i];
			result += allSymbols[i];
		}
	}
	resultEnd += "]{" + std::to_string(symbolCount) + ",})";

	if (symbolsRepeats >= 0) {
		result+= R"((?!.*(.)\1{)" + std::to_string(symbolsRepeats) + "})";
	}

	result += resultEnd;
	result += "$";

	std::regex regular = std::regex(result);

	return std::regex_match(value, regular);
}

char check::getCharValue(std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (value.size() != 1) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return value[0];
}
char check::getCharValueFromString(std::string characters, std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (value.size() != 1 || characters.find_first_of(value) == std::string::npos) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return value[0];
}
char check::getLetterValue(std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (!isLetterValue(value)) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return value[0];
}
char check::getLetterValueFromString(std::string characters, std::string outputString, std::string errorString) {
	if (!isWordValue(characters)) {
		throw "Invalid string of charactres!";
	}
	std::string value;
	std::cout << outputString << SAVE;
	std::cin >> value;
	while (!isLetterValue(value) || characters.find_first_of(value) == std::string::npos) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return value[0];
}
int check::getInt32Value(std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (!isInt32Value(value)) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	int out;
	std::istringstream is(value);

	is >> out;

	std::cin.ignore(1);
	return out;
}
int check::getInt32ValueFromTo(int leftBorder, int rightBorder, std::string outputString, std::string errorString) {
	int out;
	std::string value;
	std::cout << outputString << SAVE;

	std::cin >> value;
	std::istringstream is(value);
	while (!(isInt32Value(value) && is >> out) || out < leftBorder || out > rightBorder) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
		is.clear();
		is.str(value);
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return out;
}
int check::getNaturalValue(std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (!isNaturalValue(value)) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	int out;
	std::istringstream is(value);

	is >> out;

	std::cin.ignore(1);
	return out;
}
int check::getNaturalValueBefore(int rightBorder, std::string outputString, std::string errorString) {
	if (rightBorder < 1) {
		throw "Right border is less then 1";
	}

	int out;
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;

	std::istringstream is(value);
	while (!(isNaturalValue(value) && is >> out) || out > rightBorder) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
		is.clear();
		is.str(value);
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return out;
}
int check::getNaturalValueFromTo(int leftBorder, int rightBorder, std::string outputString, std::string errorString) {
	if (rightBorder < 1 || rightBorder - leftBorder < 1) {
		throw "Right border is less then 1";
	}

	int out;
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	std::istringstream is(value);
	while (!(isNaturalValue(value) && is >> out) || out < leftBorder || out > rightBorder) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
		is.clear();
		is.str(value);
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return out;
}
double check::getDoubleValue(std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (!isDoubleValue(value)) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	double out;
	std::istringstream is(value);

	is >> out;

	std::cin.ignore(1);
	return out;
}
double check::getDoubleValueFromTo(double leftBorder, double rightBorder, std::string outputString, std::string errorString) {
	if (rightBorder - leftBorder < 0) {
		throw "Right border is less then 1";
	}

	double out;
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	std::istringstream is(value);
	while (!(isDoubleValue(value) && is >> out) || out < leftBorder || out > rightBorder) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
		is.clear();
		is.str(value);
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return out;
}
std::string check::getWordValue(std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (!isWordValue(value)) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	std::cin.ignore(1);
	return value;
}
std::string check::getProperNameValue(std::string outputString, std::string errorString) {
	std::string value;

	std::cout << outputString << SAVE;
	std::cin >> value;
	while (!isProperNameValue(value)) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;
	return value;
}
std::string check::getPasswordValue(std::string outputString, std::string errorString, 
	int symbolCount, int uppercaseLetterCount, int lowercaseLetterCount, int numberCount, 
	int specialCharacterCount, int symbolsRepeat) {
	std::string value;

	std::cout << outputString << SAVE;
	std::getline(std::cin, value, '\n');

	while (!isPasswordValue(value, symbolCount, uppercaseLetterCount, 
		lowercaseLetterCount, numberCount, specialCharacterCount, symbolsRepeat)) {
		std::cout << REST << ERRC << errorString
			<< std::string(value.size() > errorString.size()
				? value.size() - errorString.size() : 0, ' ') << std::endl
			<< OUTC << outputString << SAVE;
		std::cin >> value;
	}
	std::cout << REST << CORC << value << std::endl << OUTC;

	return value;
}