#include "Menu.h"
#include "LoginSystem.h"
#include "checking.h"
#include <memory>
#include <string>

void Menu::startMenu() {
	system("chcp 1251>nul");

	std::shared_ptr<LoginSystem> loginSystem = LoginSystem::getInstance();
	std::shared_ptr<User> user;
	std::string login;
	std::string password;
	
	while (true) {
		system("cls");
		std::cout << "1. ����" << std::endl;
		std::cout << "2. ����������" << std::endl;
		std::cout << "3. �����" << std::endl;
		switch (check::getNaturalValueBefore(3, ">>> ", "�������� ����!")) {
		case 1:
			login = check::getWordValue("������� �����: ", "�������� ����!");
			password = check::getPasswordValue("������� ������ (���. " 
				+ std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
				" ��������): ", "�������� ����!", LoginSystem::PASSWORD_MIN_NUMBERS);
			user = (*loginSystem).LogIn(login, password);
			if (user != nullptr) {
				user->Menu();
			}
			user = nullptr;
			break;
		case 2:
			std::cout << "��� ���������� ���������� \033[33m\"������� ������� �����������"
				<< " �� ����������� ����\"\033[0m\n���� ����������� ��������� "
				<< "\033[36m��. 024402 \033[35m�������� �.�.\033[0m, 2022 �." << std::endl;
			std::cout << "��� ����������� ������� ����� �������..." << std::endl;
			system("pause>nul");
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}