#pragma once

#include <iostream>

namespace check {
	// �� ������ ��� ���������� ���������
	// P.S. ������ � ��� �������! (����� ������, �������� ��������, �� ���� �� ���� ������)
	
	bool isInt32Value(std::string value);
	// ���������, �������� �� ����� �����������
	bool isNaturalValue(std::string value);
	// ���������, �������� �� ����� � ��������� ������
	bool isDoubleValue(std::string value);
	// ���������, �������� �� ������ ������
	bool isWordValue(std::string value);
	// ���������, �������� �� ������ ������ � ������� ��������
	bool isUppercaseWordValue(std::string value);
	// ���������, �������� �� ������ ������ � ������ ��������
	bool isLovercaseWordValue(std::string value);
	// ���������, �������� �� ������ ������ ����������� (������ ����� ���������, ��������� ��������)
	bool isProperNameValue(std::string value);
	// ���������, �������� �� ������ ������
	bool isLetterValue(char value);
	bool isLetterValue(std::string value);
	// ��������� �������� �� ������ ������� �
	// - ����������� ����������� �������� symbolCount
	// - ����������� ����������� ��������� ���� uppercaseLetterCount
	// - ����������� ����������� �������� ���� lowercaseLetterCount
	// - ����������� ����������� ���� numberCount
	// - ����������� ����������� ����������� �������� specialCharacterCount
	// ���� �������� �������������, �� �������������� ������ ������� ��
	// ������ ������� � ������
	// symbolsRepeats �������� �� ���������� ���������� ������������� �������� ������
	// ���� ������ �������� �������������, �� ����������� ������� ������������
	bool isPasswordValue(std::string value, int symbolCount = 0, int uppercaseLetterCount = 0, int lowercaseLetterCount = 0, 
		int numberCount = 0, int specialCharacterCount = 0, int symbolsRepeats = -1);

	// ����������� �����:
	//
	// �������
	char getCharValue(std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// ������� �� ������
	char getCharValueFromString(std::string characters, std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// �����
	char getLetterValue(std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// ����� �� ������
	char getLetterValueFromString(std::string characters, std::string outputString = "Input character: ", std::string errorString = "Incorrect input!");
	// ������ �����
	int getInt32Value(std::string outputString = "Input integer value: ", std::string errorString = "Incorrect input!");
	// ������ ����� �� ��������� [leftBorder; rightBorder]
	int getInt32ValueFromTo(int leftBorder, int rightBorder, std::string outputString = "Input integer value: ", std::string errorString = "Incorrect input!");
	// ������������ �����
	int getNaturalValue(std::string outputString = "Input natural value: ", std::string errorString = "Incorrect input!");
	// ������������ ����� �� ��������� [1; rightBorder]
	// 1 < rightBorder
	int getNaturalValueBefore(int rightBorder, std::string outputString = "Input natural value: ", std::string errorString = "Incorrect input!");
	// ������������ ����� �� ��������� [leftBorder; rightBorder]
	// 1 <= leftBorder < rightBorder
	int getNaturalValueFromTo(int leftBorder, int rightBorder, std::string outputString = "Input natural value: ", std::string errorString = "Incorrect input!");
	// ����� � ��������� ������
	double getDoubleValue(std::string outputString = "Input float value: ", std::string errorString = "Incorrect input!");
	// ����� � ��������� ������ �� ��������� [leftBorder; rightBorder]
	// leftBorder < rightBorder
	double getDoubleValueFromTo(double leftBorder, double rightBorder, std::string outputString = "Input float value: ", std::string errorString = "Incorrect input!");
	// ����� ��� ����� �������� ����
	std::string getWordValue(std::string outputString = "Input word: ", std::string errorString = "Incorrect input!");
	// ����� � ��������� �����
	std::string getProperNameValue(std::string outputString = "Input word: ", std::string errorString = "Incorrect input!");
	// ��������� �������� �� ������ ������� �
	// - ����������� ����������� �������� symbolCount
	// - ����������� ����������� ��������� ���� uppercaseLetterCount
	// - ����������� ����������� �������� ���� lowercaseLetterCount
	// - ����������� ����������� ���� numberCount
	// - ����������� ����������� ����������� �������� specialCharacterCount
	// ���� �������� �������������, �� �������������� ������ ������� ��
	// ������ ������� � ������
	// symbolsRepeats �������� �� ���������� ���������� ������������� �������� ������
	// ���� ������ �������� �������������, �� ����������� ������� ������������
	std::string getPasswordValue(std::string outputString = "Input password: ", std::string errorString = "Incorrect input!", int symbolCount = 0,
		int uppercaseLetterCount = 0, int lowercaseLetterCount = 0, int numberCount = 0, int specialCharacterCount = 0, int symbolsRepeat = -1);
}