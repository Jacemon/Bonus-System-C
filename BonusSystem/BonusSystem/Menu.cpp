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
		std::cout << "1. Вход" << std::endl;
		std::cout << "2. Информация" << std::endl;
		std::cout << "3. Выход" << std::endl;
		switch (check::getNaturalValueBefore(3, ">>> ", "Неверный ввод!")) {
		case 1:
			login = check::getWordValue("Введите логин: ", "Неверный ввод!");
			password = check::getPasswordValue("Введите пароль (мин. " 
				+ std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
				" символов): ", "Неверный ввод!", LoginSystem::PASSWORD_MIN_NUMBERS);
			user = (*loginSystem).LogIn(login, password);
			if (user != nullptr) {
				user->Menu();
			}
			user = nullptr;
			break;
		case 2:
			std::cout << "Это консольное приложение \033[33m\"Система расчёта премиальных"
				<< " по результатам года\"\033[0m\nбыло разработано студентом "
				<< "\033[36mгр. 024402 \033[35mБеляцким Е.В.\033[0m, 2022 г." << std::endl;
			std::cout << "Для продолжения нажмите любую клавишу..." << std::endl;
			system("pause>nul");
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}