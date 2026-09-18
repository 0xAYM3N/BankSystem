#pragma once
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "../Core/clsUser.h"
#include <limits>

class clsDeleteUserScreen : protected clsScreen {
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
	static void ShowDeleteUserScreen() {
		_DrawScreenHeader("\t\t  Delete User Screen\n");

		std::string UserName = "";
		std::cout << "Enter Username: ";
		UserName = clsInputValidate::ReadString();

		while(!clsUser::IsUserExist(UserName)) {
			std::cout << "User is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'n';
		std::cout << "\nAre you sure you want to delete this user: [Y/n]: ";
		std::cin >> Answer;

		if(tolower(Answer) == 'y') {
			if(User.Delete()) {
				User.Delete();
				std::cout << "\nUser Deleted successfuly\n";
				_PrintUser(User);
			} else {
				std::cout << "\nError User Was Not Deleted\n";
			}
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
