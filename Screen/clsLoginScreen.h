#pragma once
#include <cstdlib>
#include <iostream>
#include "../Core/clsUser.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "../Core/clsGlobal.h"

class clsLoginScreen : protected clsScreen {
private:
	static bool _Login() {
		bool LoginFaild = false;
		short LoginFaildCounter = 0;

		std::string UserName, Password;
		do {
			if(LoginFaild) {
				LoginFaildCounter++;
				std::cout << "\nInvalid Username/Password\n";
				std::cout << "You have " << 3 - LoginFaildCounter << " trail(s) to login\n\n";
			}

			if(LoginFaildCounter == 3) {
				std::cout << "You are locked after 3 faild trails\n";
				return false;
			}

			std::cout << "Enter Username: ";
			std::cin >> UserName;

			std::cout << "Enter Password: ";
			std::cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while(LoginFaild);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenu();

		return true;
	}
public:
	static bool ShowLoginScreen() {
		std::system("clear");
		_DrawScreenHeader("\t\t  Login Screen\n");
		return _Login();
	}
};
