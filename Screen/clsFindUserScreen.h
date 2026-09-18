#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "../Core/clsUser.h"

class clsFindUserScreen : protected clsScreen {
private:
	static void _PrintUser(clsUser &User) {
		std::cout << "\nUser Card:";
		std::cout << "\n___________________";
		std::cout << "\nUsername    : " << User.GetUserName();
		std::cout << "\nFirstName   : " << User.GetFirstName();
		std::cout << "\nLastName    : " << User.GetLastName();
		std::cout << "\nFull Name   : " << User.FullName();
		std::cout << "\nEmail       : " << User.GetEmail();
		std::cout << "\nPhone       : " << User.GetPhone();
		std::cout << "\nPassword    : " << User.GetPassword();
		std::cout << "\nPermissions : " << User.GetPermissions();
		std::cout << "\n___________________\n";
	}
public:
	static void ShowFindUserScreen() {
		_DrawScreenHeader("\t\t  Find User Screen\n");

		std::string UserName = "";
		std::cout << "Enter Username: ";
		UserName = clsInputValidate::ReadString();

		while(!clsUser::IsUserExist(UserName)) {
			std::cout << "Username is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		if (!User.IsEmpty()) {
			std::cout << "\nUser Found :-)\n";
		} else {
			std::cout << "\nUser Was not Found :-(\n";
		}

		_PrintUser(User);
	}
};
