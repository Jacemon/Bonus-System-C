#pragma once

#include <iostream>

namespace check {
	// Всё только для английской раскладки
	// P.S. Теперь и для русской! (кроме пороля, возможно исправлю, но пока не вижу смысла)
	
	bool isInt32Value(std::string value);
	// Проверяет, является ли число натуральным
	bool isNaturalValue(std::string value);
	// Проверяет, является ли число с плавающей точкой
	bool isDoubleValue(std::string value);
	// Проверяет, является ли строка словом
	bool isWordValue(std::string value);
	// Проверяет, является ли строка словом в верхнем регистре
	bool isUppercaseWordValue(std::string value);
	// Проверяет, является ли строка словом в нижнем регистре
	bool isLovercaseWordValue(std::string value);
	// Проверяет, является ли строка именем собственным (первая буква прописная, остальные строчные)
	bool isProperNameValue(std::string value);
	// Проверяет, является ли строка буквой
	bool isLetterValue(char value);
	bool isLetterValue(std::string value);
	// Проверяет является ли строка паролем с
	// - минимальным количеством символов symbolCount
	// - минимальным количеством заглавных букв uppercaseLetterCount
	// - минимальным количеством строчных букв lowercaseLetterCount
	// - минимальным количеством цифр numberCount
	// - минимальным количеством специальных символов specialCharacterCount
	// Если значение отрицательное, то соответсвующая группа сиволов не
	// сможет входить в пароль
	// symbolsRepeats отвечает за количество допустимых повторяющихся символов подряд
	// Если данное значение отрицательное, то повторяющие символы игнорируются
	bool isPasswordValue(std::string value, int symbolCount = 0, int uppercaseLetterCount = 0, int lowercaseLetterCount = 0, 
		int numberCount = 0, int specialCharacterCount = 0, int symbolsRepeats = -1);

	// Организации ввода:
	//
	// Символа
	char getCharValue(std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// Символа из строки
	char getCharValueFromString(std::string characters, std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// Буквы
	char getLetterValue(std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// Буквы из строки
	char getLetterValueFromString(std::string characters, std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// Целого числа
	int getInt32Value(std::string outputString = "Input integer value: ", std::string errorString = "Incorrect input!");
	// Целого числа из диапазона [leftBorder; rightBorder]
	int getInt32ValueFromTo(int leftBorder, int rightBorder, std::string outputString = "Input integer value: ", std::string errorString = "Incorrect input!");
	// Натурального числа
	int getNaturalValue(std::string outputString = "Input natural value: ", std::string errorString = "Incorrect input!");
	// Натурального числа из диапазона [1; rightBorder]
	// 1 < rightBorder
	int getNaturalValueBefore(int rightBorder, std::string outputString = "Input natural value: ", std::string errorString = "Incorrect input!");
	// Натурального числа из диапазона [leftBorder; rightBorder]
	// 1 <= leftBorder < rightBorder
	int getNaturalValueFromTo(int leftBorder, int rightBorder, std::string outputString = "Input natural value: ", std::string errorString = "Incorrect input!");
	// Числа с плавающей точкой
	double getDoubleValue(std::string outputString = "Input float value: ", std::string errorString = "Incorrect input!");
	// Числа с плавающей точкой из диапазона [leftBorder; rightBorder]
	// leftBorder < rightBorder
	double getDoubleValueFromTo(double leftBorder, double rightBorder, std::string outputString = "Input float value: ", std::string errorString = "Incorrect input!");
	// Слова без учёта регистра букв
	std::string getWordValue(std::string outputString = "Input word: ", std::string errorString = "Incorrect input!");
	// Слова с заглавной буквы
	std::string getProperNameValue(std::string outputString = "Input word: ", std::string errorString = "Incorrect input!");
	// Проверяет является ли строка паролем с
	// - минимальным количеством символов symbolCount
	// - минимальным количеством заглавных букв uppercaseLetterCount
	// - минимальным количеством строчных букв lowercaseLetterCount
	// - минимальным количеством цифр numberCount
	// - минимальным количеством специальных символов specialCharacterCount
	// Если значение отрицательное, то соответсвующая группа сиволов не
	// сможет входить в пароль
	// symbolsRepeats отвечает за количество допустимых повторяющихся символов подряд
	// Если данное значение отрицательное, то повторяющие символы игнорируются
	std::string getPasswordValue(std::string outputString = "Input password: ", std::string errorString = "Incorrect input!", int symbolCount = 0,
		int uppercaseLetterCount = 0, int lowercaseLetterCount = 0, int numberCount = 0, int specialCharacterCount = 0, int symbolsRepeat = -1);
}